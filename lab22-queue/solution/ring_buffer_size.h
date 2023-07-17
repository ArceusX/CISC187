#ifndef MESA_RING_BUFFER_SIZE_H
#define MESA_RING_BUFFER_SIZE_H

#include <cstdlib>
#include <stdexcept>
#include <array>

namespace mesa {
  /**
   * A version of ring buffer that keeps track only of head and size values.
   */
  template<class T, size_t N>
    class ring_buffer {
      public:
        using value_type = T;

        ring_buffer() = default;

        constexpr 
          size_t capacity() const noexcept { return N; }

        constexpr 
          void clear() noexcept { size_ = 0; }

        constexpr 
          size_t size() const noexcept { return size_; }

        constexpr 
          bool  empty() const noexcept { return size_ == 0; }

        constexpr 
          bool  full()  const noexcept { return size_ == N; }

        void push(const T& value) {
          if (full()) {
            throw std::domain_error("Can't write to full buffer");
          }
          data_[tail()] = value;
          ++size_;
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
        std::array<T,N> data_ {};
        size_t head_ = 0;
        size_t size_ = 0;

        constexpr 
          size_t tail() const noexcept { 
            return (head_+size_) % N;
          }

        constexpr 
          void move_head() noexcept {
            head_ = (head_+1) % N;
            --size_;
          }
    };
}  // namespace mesa

#endif // MESA_RING_BUFFER_H

