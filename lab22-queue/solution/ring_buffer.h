#ifndef MESA_RING_BUFFER_TAIL_H
#define MESA_RING_BUFFER_TAIL_H

#include <cassert>
#include <cstdlib>
#include <stdexcept>
#include <array>

namespace mesa {
  /**
   * A version of ring buffer that keeps track only of head and tail values.
   *
   * The class uses a 'dummy' storage position to allow the tail to
   * always refer to the element one past the end of the data.
   */
  template<class T, size_t N>
    class ring_buffer {
      public:
        using value_type = T;

        // We are fibbing to the users a bit here.
        // This is the capacity availabe to them,
        // but it is one less than the actual array storage.
        constexpr 
          size_t capacity() const noexcept { return N; }

        constexpr 
          void clear() noexcept { head_ = tail_; }

        /**
         * Compute the current size.
         */
        constexpr 
          size_t size() const noexcept { 
            // using a ternary for backwards compatibility
            // with C++11 constexpr
            return tail_ >= head_ ?
                   tail_ - head_  : 
                   true_capacity_ - head_ + tail_;
          }

        constexpr 
          bool  empty() const noexcept { return head_ == tail_; }

        constexpr 
          bool  full()  const noexcept { return size() == N; }

        void push(const T& value) {
          if (full()) {
            throw std::domain_error("Can't write to full buffer");
          }
          data_[tail_] = value;
          move_tail();
        }

        T pop() {
          if (empty()) {
            throw std::domain_error("Can't read an empty buffer");
          }
          const auto& value = data_[head_];
          move_head();
          return value;
        }
        
        /**
         * Continue writing to a full buffer.
         *
         * If the buffer is not full, then just `push`.
         * If the buffer is full, then replace the **oldest**
         * element in the ring.
         */
        void overwrite(const T& value) {
          if(full()) { // replace head value
            move_head();
          }
          push(value);
        }

      private:
        // The extra storage location is used by tail_.
        // This ensures there is always 1 empty spot for the tail
        // to refer to.
        std::array<T,N+1> data_ {};
        size_t head_ = 0;
        size_t tail_ = 0;
        // This is the actual size of the array.
        // Users get access to N elements.
        const size_t true_capacity_ = N+1;

        constexpr 
          void move_tail() noexcept { 
            tail_ = (tail_+1) % true_capacity_;
          }

        constexpr 
          void move_head() noexcept {
            head_ = (head_+1) % true_capacity_;
          }
    };
}  // namespace mesa

#endif // MESA_RING_BUFFER_H

