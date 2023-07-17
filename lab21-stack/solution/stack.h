#ifndef MESA_CISC187_STACK_H
#define MESA_CISC187_STACK_H

#include <cstddef>
#include <type_traits>
#include <utility>

#include "bag.h"

namespace mesa {

  /**
   * A value class to expose the behaviors of a stack,
   * a LIFO (last-in, first-out) data structure.
   */
  template<class T, class Container = bag<T>>
    class stack {
      private:
        Container c;
      public:
        typedef Container                           container_type;
        typedef typename container_type::value_type value_type;
        static_assert((std::is_same<T, value_type>::value), 
            "stack type must match underlying container value type" );

        stack() = default;
        stack(const stack<T>& other)
          : c{other.c}
        {}
        /**
         * Create a stack from a container.
         */
        explicit
        stack(const container_type& other)
          : c{other}
        { }

        /**
         * Replace values from a stack into the current stack.
         */
        stack<T>& operator=(const stack<T>& other)
        {
          c = other.c;
          return *this;
        }

        // move construct
        stack(stack<T>&& other)
          : c{std::move(other.c)}
        { }
        // move assign
        stack<T>& operator=(stack<T>&& other)
        {
          c = std::move(other.c);
          return *this;
        }

        constexpr 
          bool empty()   const noexcept { return c.empty(); }
        constexpr 
          size_t size()  const noexcept { return c.size(); }

        /**
         * Returns reference to the top of the stack.
         * Calling top on an empty container causes undefined behavior.
         */
        T& top() { return c.back(); }
        constexpr
          const T& top() const noexcept { return c.back(); }

        /**
         * Push a new value on top of the stack.
         */
        void push(const T& value)  { c.push_back(value); }
        void push(const T&& value) { c.push_back(std::move(value)); }

        void pop() { return c.pop_back(); }

        // Regular
        template <class T1, class C1>
          friend
          bool
          operator==(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs)
          {
            return lhs.c == rhs.c;
          }

        // Totally ordered
        template <class T1, class C1>
          friend
          bool
          operator< (const stack<T1, C1>& lhs, const stack<T1, C1>& rhs)
          {
            return lhs.c < rhs.c;
          }
    };

} // end namespace mesa

// Regular
template<class T, class Container>
inline
bool operator!=(const mesa::stack<T, Container>& lhs, 
                const mesa::stack<T, Container>& rhs) {
  return !(lhs == rhs);
}

// Totally ordered
template<class T, class Container>
inline
bool operator>(const mesa::stack<T, Container>& lhs, 
               const mesa::stack<T, Container>& rhs) {
  return rhs < lhs;
}
template<class T, class Container>
inline
bool operator<=(const mesa::stack<T, Container>& lhs, 
                const mesa::stack<T, Container>& rhs) {
  return !(lhs > rhs);
}
template<class T, class Container>
inline
bool operator>=(const mesa::stack<T, Container>& lhs, 
                const mesa::stack<T, Container>& rhs) {
  return !(lhs < rhs);
}

#endif

