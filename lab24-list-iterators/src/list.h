#ifndef MESA_CISC187_LIST
#define MESA_CISC187_LIST

#include <iostream>
#include <algorithm>
#include <cstddef>

namespace mesa {

    template <typename T>
    struct list_node;

    template <typename T>
    class list_iterator;

    template <typename T>
    class list {

    private:
        list_node<T>* head;
        size_t length;

    public:
        using value_type = T;
        using Node = list_node<T>;
        using iterator = list_iterator<T>;

        list() : head(nullptr), length(0) {}

        list(const T& value) : head(new Node(value)), length(1) {}

        list(std::initializer_list<T> list): list() {            
            for (const T& value: list) {
                push_front(value);
            }
        }

        void push_front(const T& value) {
            head = new Node(value, head);
            length++;
        }

        constexpr T& front() const {
            return head->value;
        }

        T& front() {
            return head->value;
        }

        constexpr size_t size() const noexcept {
            return length;
        }

        constexpr bool empty() const noexcept {
            return !head;
        }

        void pop_front() {
            if (head) {

                // Record, increment, then delete record
                Node* to_delete = head;
                head = head->next;
                delete to_delete;

                length--;
            }
        }

        iterator insert_after(iterator pos, const T& value) {
            if (!(pos.node)) return iterator();

            pos.node->next = new Node(value, pos.node->next);
            length++;

            return iterator(pos.node->next);
        }

        iterator erase_after(iterator pos) {
            if (!pos.node || !(pos.node->next)) return iterator();

            Node* to_delete = pos.node->next;
            pos.node->next = to_delete->next;
            delete to_delete;

            length--;
            return iterator(pos.node->next);
        }

        iterator begin() {
            return iterator(head);
        }

        constexpr const iterator begin() const noexcept {
            return iterator(head);
        }

        iterator end() {
            return iterator();
        }

        constexpr const iterator end() const noexcept {
            return iterator();
        }

        list(const list&) = delete;
        list(list&&) = delete;

        list& operator=(const list<T>&) = delete;
        list& operator=(list<T>&&) = delete;

        ~list() {
            Node* current = head;

            while (current) {
                Node* next = current->next;
                delete current;
                current = next;
            }
        }
    };

    template <typename T>
    struct list_node {
        T value;
        list_node* next;
        explicit list_node(const T& v, list_node* next = nullptr)
            : value(v), next(next) { };
    };

    template <typename T>
    class list_iterator {
    public:
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef ptrdiff_t difference_type;
        typedef std::forward_iterator_tag iterator_category;

        list_node<T>* node;

        list_iterator() : node(nullptr) {}

        list_iterator(list_node<T>* node) : node(node) {}

        const T& operator *() const {
            return node->value;
        }

        list_iterator<T>& operator++() {
            node = node->next;
            return *this;
        }

        // (int) shows postfix: return prev before ++ing 
        list_iterator<T> operator++(int) {
            list_iterator<T> new_iterator = list_iterator<T>(node->next);
            node = node->next;
            return new_iterator;
        }
    };

    template <typename T>
    inline bool operator==(const list_iterator<T> lhs, const list_iterator<T> rhs) {
        return lhs.node == rhs.node;
    }

    template <typename T>
    inline bool operator!=(const list_iterator<T> lhs, const list_iterator<T> rhs) {
        return lhs.node != rhs.node;
    }
}

#endif