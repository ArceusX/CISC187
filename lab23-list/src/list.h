#ifndef MESA_CISC187_LIST
#define MESA_CISC187_LIST

#include <iostream>
#include <algorithm>

namespace mesa {

    template <typename T>
    struct list_node {
        T value;
        list_node* next;

        explicit list_node(const T& v, list_node* next = nullptr)
            : value(v), next(next) { };
    };

    template <typename T>
    class list {
    private:
        list_node<T>* head;
        size_t length;

    public:
        using value_type = T;
        using Node = list_node<T>;

        list(): head(nullptr), length(0) {}

        list(const T& value) : head(new Node(value)), length(1) {}

        list(std::initializer_list<T> src): list() {            
            for (const T& value: src) {
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

        void insert_after(const int pos, const T& value) {
            if (!head || pos < 0) return;

            Node* current = head;
            for (int i = pos; i > 0 && current->next; i--) {
                current = current->next;
            }

            // Precursor to point to new node and
            // new node to point to previous successor
            current->next = new Node(value, current->next);
            length++;
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
}

#endif