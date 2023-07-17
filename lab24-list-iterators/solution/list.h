#ifndef MESA_CISC187_LIST_H
#define MESA_CISC187_LIST_H

#include <cstddef>
#include <iostream>
#include <initializer_list>
#include <iterator>  // forward_iterator_tag

// Support structures for a linked list
namespace mesa {

  template <class T>
  struct list_node {
    T value;
    list_node* next;
    explicit
      list_node(const T& v, list_node* next = nullptr) 
      : value{v}
      , next{next}
    { }
  };

  template <typename T>
  struct list_iterator {
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    list_iterator() = default;
    explicit
    list_iterator(list_node<T>* n) 
      : node{n} 
    { }

    constexpr
    T& operator*() const {
      return node->value;
    }

    list_iterator& operator++() 
    { 
      node = node->next;
      return *this; 
    }
    // What is the '&' doing after the parameter list?
    // This overload is defined only when the this pointer
    // is an lvalue reference.
    // 
    // The motivation is to prevent code like this:
    //     (it++)++
    // which if we allowed it, would mean that we are
    // incrementing the tmp object returned from this function.
    list_iterator operator++(int) & {
      list_iterator tmp(*this); 
      ++*this; 
      return tmp;
    }

    list_node<T>* node;
  };

} // end namespace mesa

// Regular
template <class T>
inline
bool operator==(const mesa::list_iterator<T>& lhs, 
                const mesa::list_iterator<T>& rhs) {
  return lhs.node == rhs.node;
}
template <class T>
inline
bool operator!=(const mesa::list_iterator<T>& lhs, 
                const mesa::list_iterator<T>& rhs) {
  return !(lhs == rhs);
}




namespace mesa {
  // a singly linked list with an iterator
  template <class T>
    class list {
      private:
        list_node<T>* head = nullptr;  // always points to the first node in the list
        size_t sz = 0;

      public:
        using value_type = T;
        using iterator   = list_iterator<T>;

        list() = default;
        explicit
          list(const T& value)
          : head{new list_node<T>{value}}
          , sz {1}
        { }

        list (const list&) = delete;
        list (list&&) = delete;

        list& operator=(const list<T>&) = delete;
        list& operator=(list<T>&&) = delete;

        ~list() {
          while (!empty()) {
            pop_front();
          }
        }

        constexpr
          iterator begin() const noexcept { return iterator(head); }
        constexpr
          iterator end()   const noexcept { return iterator(nullptr); }

        iterator   begin() noexcept { return iterator(head); }
        iterator   end()   noexcept { return iterator(nullptr); }

        // Inserts a new value after the iterator position in the list
        // position should be >= head and < tail
        // To insert a new head, use push_front
        iterator insert_after(iterator it, const T& value) {
          auto node = new list_node<T>{value, it.node->next};
          it.node->next = node;
          ++sz;
          return iterator(node);
        }

        // Erases the value after the iterator position in the list
        // position should be >= head and < tail
        // To erase the head, use pop_front
        iterator erase_after(iterator it) {
          auto trash = it.node->next;
          it.node->next = trash->next;
          delete trash;
          --sz;
          return iterator(it.node->next);
        }

        // Inserts a new value at the beginning of the list
        void push_front(const T& value) {
          auto node = new list_node<T>{value, head};
          head = node;
          ++sz;
        }

        // return a reference to the beginning of the list
        constexpr
          const T& front() const noexcept {
            return head->value;
          }
        T& front() {
          return head->value;
        }

        // deletes the first element in the list
        void pop_front() {
          if (empty()) { return; }
          auto trash = head;
          head = head->next;
          delete trash;
          --sz;
        }


        // test if the linked list is empty
        constexpr
        bool empty() const noexcept { return head == nullptr; }
        // return the number of elements in the list
        constexpr
        size_t size() const noexcept { return sz; }

    };

} // end namespace mesa

template <class T>
std::ostream& operator<< (std::ostream& os, const mesa::list<T>& rhs) {
  os << '[';
  for (auto it = rhs.begin(); it != rhs.end(); ++it) {
    os << *it;
    if (it.node->next != nullptr) {
      os << ", ";
    }
  }
  return os << ']';
}

#endif

