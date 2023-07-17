#ifndef MESA_CISC187_ARRAY_H
#define MESA_CISC187_ARRAY_H

#include <algorithm>
#include <cstddef>
#include <initializer_list>

namespace mesa {

  /**
   * A value class to encapsulate a fixed size array.
   */
  template<class T, size_t N>
    class array {
      private:
        T data_[N] = {};
      public:
        using value_type = T;
        // same as:
        // typedef T value_type;

        array() = default;

        /**
         * Construct an array from an initializer list.
         *
         * @throw std::bad_alloc if copy fails to allocate memory
         */
        explicit
          array(std::initializer_list<T> list) {
            std::copy(list.begin(), list.end(), data_);
          }

        constexpr 
          bool empty()   const noexcept { return begin() == end(); }
        constexpr 
          size_t size()  const noexcept { return N; }

        // iterators
        constexpr
          const T* begin() const noexcept { 
            return data_;
          }
        constexpr
          const T* end() const noexcept { 
            return data_+N;
          }
        T* begin() { 
            return data_;
        }
        T* end() { 
            return data_+N;
        }

    };


} // end namespace mesa

#endif

