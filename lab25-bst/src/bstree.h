#ifndef MESA_CISC187_BINARY_SEARCH_TREE_H
#define MESA_CISC187_BINARY_SEARCH_TREE_H

#include <cstddef>
#include <iostream>
#include <type_traits>
#include <utility>

#include "tree_node.h"

namespace mesa {

    template <typename T,
        typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    struct tree_iterator {

        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef std::ptrdiff_t difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;

        using Node = tree::tree_node<T>;

        tree_iterator() = default;
        tree_iterator(const Node* node) : node {node} {}

        constexpr const T& operator*() const noexcept {
            return node->value;
        }

        // Get inorder successor of node referenced by iterator
        // Inorder successor is either 1 of 2 options, depending
        // on whether right child/subtree exists
        tree_iterator& operator++() {
            if (node) {
                node = tree::getInorderSuccessor(node);
            }

            return *this;
        }

        // Get inorder predecessor of node referenced by iterator
        // Inorder predecessor is either 1 of 2 options, depending
        // whether left child/subtree exists
        tree_iterator& operator--() {
            if (node) {
                node = tree::getInorderPredecessor(node);
            }

            return *this;
        }

        tree_iterator operator++(int) {
            tree_iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        tree_iterator operator--(int) {
            tree_iterator tmp(*this);
            --(*this);
            return tmp;
        }

        const Node* node;
    };
}

template <class T>
inline bool operator==(const mesa::tree_iterator<T>& lhs, 
    const mesa::tree_iterator<T>& rhs) {
    return lhs.node == rhs.node;
}

template <class T>
inline bool operator!=(const mesa::tree_iterator<T>& lhs, 
    const mesa::tree_iterator<T>& rhs) {
    return !(lhs == rhs);
}

namespace mesa {

    template<class T>
    class bstree {
    public:
        typedef T value_type;
        typedef tree::tree_node<T> Node;
        typedef const tree_iterator<T> const_iterator;
        typedef const_iterator iterator;
        typedef const_iterator reverse_iterator;
        typedef const_iterator const_reverse_iterator;

        bstree() = default;

        bstree(Node* root):
            root(mesa::tree::deep_copy(root)) {}

        bstree(std::initializer_list<T> list) {
            for (const T& val : list) insert(val);
        }

        explicit bstree(const T& value): root {new Node{value}} {}

        bstree(const bstree& other):
            root(mesa::tree::deep_copy(other.root)) {}

        bstree(bstree&& other) {
            root = other.root;
            other.root = nullptr;
        }

        // Newly created other to hold deep copy of passed
        // obj's members. other passed old this->root and 
        // destructs that data once it exits scope
        bstree& operator=(bstree other) noexcept {
            std::swap(root, other.root);
            return *this;
        }

        bstree& operator=(bstree&& other) noexcept {
            std::swap(root, other.root);
            return *this;
        }

        ~bstree() {
            erase();
        }

        void erase() {
            mesa::tree::eraseTree(root);
        }

        void erase(const T& value) {
            root = tree::erase(value, root);
        }

        constexpr bool empty() const noexcept { return !root; }

        bool contains(const T& value) const noexcept {
            return tree::contains(value, root);
        }

        const_iterator find(const T& value) const noexcept {
            return const_iterator(tree::find(value, root));
        }

        const_iterator insert(const T& value) {

            if (!root) {
                root = new Node(value);
                return const_iterator(root);
            }

            // Found existing node with value. Do not insert duplicate
            Node* parent = tree::find(value, root);
            if (parent->value == value) return const_iterator(parent);

            Node* inserted = new Node(value);
            if (parent->value < value) {
                parent->right = inserted;
            }
            else {
                parent->left = inserted;
            }
            inserted->parent = parent;

            return const_iterator(inserted);
        }

        iterator begin() {
            return iterator(tree::min_element(root));
        }

        constexpr const iterator begin() const noexcept {
            return iterator(tree::min_element(root));
        }

        iterator rbegin() {
            return iterator(tree::max_element(root));
        }

        constexpr const iterator rbegin() const noexcept {
            return iterator(tree::max_element(root));
        }

        iterator end() {
            return iterator(nullptr);
        }

        constexpr const iterator end() const noexcept {
            return iterator(nullptr);
        }

        iterator rend() {
            return iterator(nullptr);
        }

        constexpr const iterator rend() const noexcept {
            return iterator(nullptr);
        }

    private:
        Node* root = nullptr;

        friend std::ostream& operator<<(std::ostream& os, const bstree& node) {
            return os << node.root;
        }
    };
}

#endif

