#ifndef MESA_CISC187_ARRAY_H
#define MESA_CISC187_ARRAY_H

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace mesa {

  /**
   * A value class to encapsulate a fixed size array.
   */
  template<class T, size_t N>
    class array {
      private:
        T data_[N];
        const char* message_ = "array index out of range";
      public:
        using value_type =  T;

        /**
         * Construct a default initialized array.
         *
         * All values will initialized to the default value for
         * the value type T.
         * @throw std::bad_alloc if fill fails to allocate memory
         */
        // Note: alternatively, could init data_ as:
        //    T data_[N] = {};
        // and then use 
        //   array() = default; 
        // here
        array()
        {
          std::fill(begin(), end(), T{});
        }

        /**
         * Construct an array from an initializer list.
         *
         * @throw std::bad_alloc if copy fails to allocate memory
         */
        explicit
          array(std::initializer_list<T> list) {
            std::copy(list.begin(), list.end(), static_cast<T*>(data_));
          }

        // element access
        constexpr
          const T& operator[](const size_t& index) const { return data_[index]; }
        constexpr
                T& operator[](const size_t& index)       { return data_[index]; }

        /**
         * Range checked element access.
         *
         * @throw std::out_of_range if !(index < size())
         */
        constexpr
          const T& at(size_t index) const { 
            if (!(index < size())) {
              throw std::out_of_range(message_);
            }
            return data_[index]; 
          }
        constexpr
          T& at(size_t index) { 
            if (!(index < size())) {
              throw std::out_of_range(message_);
            }
            return data_[index]; 
          }

        constexpr 
          bool empty()   const noexcept { return begin() == end(); }
        constexpr 
          size_t size()  const noexcept { return N; }

        //pointer to storage
        T* data()                   { return static_cast<T*>(data_); }
        constexpr
          const T* data() const     { return static_cast<const T*>(data_); }

        /**
         * Returns reference to the last element in the container.
         * Calling back on an empty container causes undefined behavior.
         */
        T& back() { return *(data_ + N-1); }
        constexpr
          const T& back() const noexcept { return *(data_ + N-1); }

        // iterators
        constexpr
          const T* begin() const noexcept {
            return static_cast<const T*>(data_);
          }
        constexpr
          const T* end() const noexcept {
            return static_cast<const T*>(data_)+N;
          }
        T* begin() {
            return static_cast<T*>(data_);
        }
        T* end() {
            return static_cast<T*>(data_)+N;
        }

    };


} // end namespace mesa

  // Regular
template<class T, size_t N>
  inline
  bool operator==(const mesa::array<T,N>& lhs, const mesa::array<T,N>& rhs) {
    return std::equal(lhs.begin(), lhs.end(), 
                      rhs.begin());
  }
template<class T, size_t N>
  inline
  bool operator!=(const mesa::array<T,N>& lhs, const mesa::array<T,N>& rhs) {
     return !(lhs == rhs);
  }

  // Totally ordered
template<class T, size_t N>
  inline
  bool operator<(const mesa::array<T,N>& lhs, const mesa::array<T,N>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), 
                                        rhs.begin(), rhs.end());
  }
template<class T, size_t N>
  inline
  bool operator>(const mesa::array<T,N>& lhs, const mesa::array<T,N>& rhs) {
     return rhs < lhs;
  }
template<class T, size_t N>
  inline
  bool operator<=(const mesa::array<T,N>& lhs, const mesa::array<T,N>& rhs) {
     return !(lhs > rhs);
  }
template<class T, size_t N>
  inline
  bool operator>=(const mesa::array<T,N>& lhs, const mesa::array<T,N>& rhs) {
     return !(lhs < rhs);
  }

#endif

