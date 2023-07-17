#ifndef MESA_CISC187_BAG_H
#define MESA_CISC187_BAG_H

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace mesa {

  /**
   * A value class to encapsulate a container that can grow and shrink
   */
  template<class T>
    class bag {
      private:
        size_t capacity_ {0};
        size_t size_     {0};
        T* data_         {nullptr};
      public:
        using value_type = T;

        /**
         * Construct an empty bag.
         */
        bag() = default;

        /**
         * Construct a default initialized bag of specified size.
         *
         * All values will initialized to the default value for
         * the value type T.
         * @throw std::bad_alloc if fill fails to allocate memory
         */
        explicit
          bag(size_t size)
            : capacity_{size}
            , size_{capacity_}
            , data_{new T[size_]}
          {
            std::fill(begin(), end(), T{});
          }

        /**
         * Construct an bag from an initializer list.
         *
         * @throw std::bad_alloc if copy fails to allocate memory
         */
        explicit
          bag(std::initializer_list<T> list) 
            : capacity_{list.size()}
            , size_{capacity_}
            , data_{new T[capacity_]}
          {
            std::copy(list.begin(), list.end(), data_);
          }

        // destructor
        ~bag() 
        { 
          delete[] data_; 
        }

        // copy constructor
        bag(const bag<T>& other)
          : capacity_{other.capacity()}
          , size_{other.size()}
          , data_{new T[capacity_]}
        {
          std::copy(other.begin(), other.end(), data_);
        }

        // move construct
        bag(bag<T>&& other) noexcept
          : capacity_{std::move(other.capacity_)}
          , size_{std::move(other.size_)}
          , data_{std::move(other.data_)}
        {
        }

        /**
         * Assign values from a bag into the current bag.
         *
         * @throw std::bad_alloc if copy fails to allocate memory
         * If an exception is thrown, this function has no effect 
         * (strong exception guarantee).
         */
        bag<T>& operator=(const bag<T>& other)
        {
          // solution 1
          bag(other).swap(*this); // swap(*this, bag(other));
          return *this;
          // solution 2
          // check self assignment
          // if (&other == this) {
          //   return *this;
          // }
          // T* new_data = new T[other.capacity()];
          // std::copy(other.begin(), other.end(), new_data);
          // delete[] data_;
          // data_ = new_data;
          // capacity_ = other.capacity();
          // size_ = other.size();
          // return *this;
        }

        void swap(bag<T>& rhs) {
          std::swap(capacity_, rhs.capacity_);
          std::swap(size_, rhs.size_);
          std::swap(data_, rhs.data_);
        }

        // move assign
        bag<T>& operator=(bag<T>&& other) noexcept
        {
          delete[] data_;
          capacity_ = std::move(other.capacity_);
          data_ = std::move(other.data_);
          size_ = std::move(other.size_);
          return *this;
        }

        // Bag capacity
        constexpr 
          bool empty()       const noexcept { return begin() == end(); }
        constexpr 
          size_t capacity()  const noexcept { return capacity_; }
        constexpr 
          size_t size()      const noexcept { return size_; }

        //
        // element access
        //
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
          const T& at(const size_t& index) const { 
            if (!(index < size())) {
              throw std::out_of_range("bag index out of range");
            }
            return data_[index]; 
          }
        constexpr
          T& at(const size_t& index) { 
            if (!(index < size())) {
              throw std::out_of_range("bag index out of range");
            }
            return data_[index]; 
          }

        //pointer to storage
        T* data()                   { return data_; }
        constexpr
        const T* data() const       { return data_; }

        /**
         * Returns reference to the last element in the container.
         * Calling back on an empty container causes undefined behavior.
         */
        T& back() { return *(data_ + size_-1); }
        constexpr
          const T& back() const noexcept { return *(data_ + size_-1); }

        // iterators
        constexpr
          const T* begin() const noexcept { return data_; }
        constexpr
          const T* end()   const noexcept { return data_ + size_; }
        T* begin()                { return data_; }
        T* end()                  { return data_ + size_; }

    };

} // end namespace mesa

// Regular
template<class T>
inline
bool operator==(const mesa::bag<T>& lhs, const mesa::bag<T>& rhs) {
  return std::equal(lhs.begin(), lhs.end(), 
      rhs.begin());
}
template<class T>
inline
bool operator!=(const mesa::bag<T>& lhs, const mesa::bag<T>& rhs) {
  return !(lhs == rhs);
}

// Totally ordered
template<class T>
inline
bool operator<(const mesa::bag<T>& lhs, const mesa::bag<T>& rhs) {
  return std::lexicographical_compare(lhs.begin(), lhs.end(), 
      rhs.begin(), rhs.end());
}
template<class T>
inline
bool operator>(const mesa::bag<T>& lhs, const mesa::bag<T>& rhs) {
  return rhs < lhs;
}
template<class T>
inline
bool operator<=(const mesa::bag<T>& lhs, const mesa::bag<T>& rhs) {
  return !(lhs > rhs);
}
template<class T>
inline
bool operator>=(const mesa::bag<T>& lhs, const mesa::bag<T>& rhs) {
  return !(lhs < rhs);
}

#endif

