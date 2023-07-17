#ifndef MESA_CISC187_LIST_H
#define MESA_CISC187_LIST_H

#include <cstddef>
#include <iostream>

// A simple singly-linked list
namespace mesa {

  template <class T>
  struct list_node {
    T value;
    list_node* next;
    explicit list_node(const T& v, list_node* next = nullptr) 
      : value{v}
      , next{next}
    { }
  };

  template <class T>
    class list {

      public:
        using value_type = T;

        list() = default;
        explicit list(const T& value)
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

        // Inserts a new value after the zero-based position in the list
        // position should be >= 0 and <= size
        // To insert a new head, use push_front
        void insert_after(const int pos, const T& value) {
          auto cursor = move_cursor(pos);
          auto tmp = cursor->next;
          auto node = new list_node<T>{value, tmp};
          cursor->next = node;
          ++sz;
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
          if (empty()) return;
          auto trash = head;
          head = head->next;
          delete trash;
          --sz;
        }


        constexpr
        bool empty() const noexcept { return head == nullptr; }
        constexpr
        size_t size() const noexcept { return sz; }

      private:
        list_node<T>* head = nullptr;  // always points to the first node in the list
        size_t sz = 0;

        /**
         * Return a pointer to the 'N-th' node in the list.
         * @param pos a zero-based count of the list nodes.
         * @return a list_node pointer.
         *         If the list is empty,
         *         then the pointer will == `nullptr`
         */
        list_node<T>* move_cursor(const int pos) const {
          int count = 0;
          auto cursor = head;
          while (count < pos && cursor->next != nullptr) {
            cursor = cursor->next;
            ++count;
          }
          return cursor;
        }

        // a friend function because this simple class 
        // needs access to private members to print
        // TODO: this is a simple iterator.
        // It should not be buried inside operator<<
        // Adding an iterator would fix this
          friend
          std::ostream& operator<< (std::ostream& os, const list& rhs) {
            auto cursor = rhs.head;
            os << '[';
            while (cursor != nullptr) {
              os << cursor->value;
              cursor = cursor->next;
              if (cursor != nullptr) {
                os << ", ";
              }
            }
            return os << ']';
          }
    };

} // end namespace mesa

#endif


