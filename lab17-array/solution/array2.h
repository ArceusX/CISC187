#ifndef MESA_CISC187_ARRAY_H
#define MESA_CISC187_ARRAY_H

#include <algorithm>
#include <cstddef>
#include <initializer_list>

namespace mesa {

  /**
   * A value class to encapsulate a fixed size array.
   *
   * This class is is bit more pedantic about the types
   * returned from begin and end.
   */
  template<class T, size_t N>
    class array {
      private:
        T data_[N];
      public:
        using value_type = T;
        // same as:
        // typedef T value_type;

        /**
         * Construct a default initialized array.
         *
         * All values will initialized to the default value for
         * the value type T.
         * @throw std::bad_alloc if fill fails to allocate memory
         */
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

        constexpr 
          bool empty()   const noexcept { return begin() == end(); }
        constexpr 
          size_t size()  const noexcept { return N; }

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

#endif

