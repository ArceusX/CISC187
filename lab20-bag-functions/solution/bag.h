#ifndef MESA_CISC187_BAG_H
#define MESA_CISC187_BAG_H

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace mesa {

  /**
   * A value class to encapsulate a container that can grow and shrink.
   */
  template<class T>
    class bag {
      private:
        size_t capacity_;
        size_t size_;
        T* data_;
      public:
        typedef T value_type;

        /**
         * Construct an empty bag.
         */
        bag()
          : capacity_{0}
          , size_{0}
          , data_{nullptr}
        {
        }

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
        bag(bag<T>&& other)
          : capacity_{std::move(other.capacity_)}
          , size_{std::move(other.size_)}
          , data_{std::move(other.data_)}
        {
          other.capacity_ = other.size_ = 0;
          other.data_ = nullptr;
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
          bag(other).swap(*this);
          return *this;
          // if (this == &other) return *this;  // self-assignment
          // if (other.size_ < capacity_) {
          //   std::copy(other.begin(), other.end(), data_);
          //   size_ = other.size_;
          //   return *this;
          // }
          // T* new_data = new T[other.capacity()];
          // std::copy(other.begin(), other.end(), new_data);
          // delete[] data_;
          // data_ = new_data;
          // capacity_ = size_ = other.size_;
          // return *this;
        }
        
        /**
         * Specialize std::swap for a bag.
         */
        void swap(bag<T>& other) {
          std::swap(capacity_, other.capacity_);
          std::swap(size_, other.size_);
          std::swap(data_, other.data_);
        }

        // move assign
        bag<T>& operator=(bag<T>&& other)
        {
          // solution 1
          bag(std::move(other)).swap(*this);
          other.data_ = nullptr;
          return *this;
          // delete[] data_;
          // capacity_ = size_ = other.size_;
          // data_ = other.data_;
          // other.capacity_ = other.size_ = 0;
          // other.data_ = nullptr;
          // return *this;
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
          const T& at(const size_t& index) const { 
            if (!(index < size())) throw std::out_of_range("bag index out of range");
            return data_[index]; 
          }
        constexpr
          T& at(const size_t& index) { 
            if (!(index < size())) throw std::out_of_range("bag index out of range");
            return data_[index]; 
          }

        constexpr 
          bool empty()   const noexcept { return begin() == end(); }
        constexpr 
          size_t capacity()  const noexcept { return capacity_; }
        constexpr 
          size_t size()  const noexcept { return size_; }

        //pointer to storage
        T* data() { return data_; }
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

        /**
         * Increase the capacity of the bag to a value that's 
         * greater or equal to new_capacity. 
         * If new_capacity is greater than the current capacity(),
         * new storage is allocated, otherwise the method does nothing.
         *
         * reserve() does not change the size of the bag.
         *
         * If new_capacity is greater than capacity(), all iterators,
         * including the past-the-end iterator,
         * and all references to the elements are invalidated.
         * Otherwise, no iterators or references are invalidated.
         */
        void reserve(size_t new_capacity)
        {
          if (new_capacity <= capacity_) {
            return;
          }
          T* new_data = new T[new_capacity];
          std::copy(begin(), end(), new_data);
          delete[] data_;
          data_ = new_data;
          capacity_ = new_capacity;
        }

        /**
         * Resizes the container to contain count elements.
         *
         * If the current size is greater than count,
         * the container is reduced to its first count elements.
         *
         * If the current size is less than count,
         * additional default-inserted elements are appended.
         */
        void resize(size_t new_capacity)
        {
          reserve(new_capacity);
          std::fill(begin()+size_, begin()+capacity_, T{});
          // for (size_t i = size_; i < capacity_; ++i) {
          //   data_[i] = T{};
          // }
          size_ = new_capacity;
        }

        /**
         * Appends the given element value to the end of the container.
         *
         * The new element is initialized as a copy of value.
         */
        void push_back(T value)
        {
          if(capacity_ == 0) {
            reserve(1);
          } else if (size_ == capacity_) {
            reserve(2*capacity_);
          }
          data_[size_] = value;
          ++size_;
        }

        /**
         * Removes the last element of the container.
         *
         * Calling pop_back on an empty container is undefined.
         *
         * Iterators and references to the last element, 
         * as well as the end() iterator, are invalidated.
         */
        void pop_back()
        {
          if(!empty()) --size_;
        }

    };

} // end namespace mesa

// Regular
template<class T>
inline
bool operator==(const mesa::bag<T>& lhs, const mesa::bag<T>& rhs) {
  return std::equal(lhs.begin(), lhs.end(), rhs.begin());
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

