#ifndef MESA_CISC187_TREE_NODE_H
#define MESA_CISC187_TREE_NODE_H

#include <iostream>
#include <algorithm>

namespace mesa {
    namespace tree {

        template<class T>
        struct tree_node {

            T value;
            tree_node<T> *left, *right, *parent;

            // T {}: default initialization of T
            tree_node(
                const T& value = T{},
                tree_node<T>* left = nullptr,
                tree_node<T>* right = nullptr,
                tree_node<T>* parent = nullptr):
                value {value}, left {left}, right {right}, parent {parent} { }
        };

        template <class T>
        bool contains(const T& value, tree_node<T>* root) {
            tree_node<T>* f = find(value, root);

            return (f && f->value == value);
        }

        // Deep copy creates actual new nodes
        template <class T>
        tree_node<T>* deep_copy(tree_node<T>* root) {

            if (!root) return nullptr;
            return new tree_node<T> (
                root->value,
                deep_copy(root->left),
                deep_copy(root->right),
                root->parent
                );
        }

        template <typename T>
        void eraseTree(tree_node<T>* root, bool toRewire = true) {
            if (root) {
                eraseTree(root->left, false);
                eraseTree(root->right, false);

                if (toRewire && root->parent) {
                    if (root == root->parent->left) {
                        root->parent->left = nullptr;
                    }
                    else root->parent->right = nullptr;
                }

                delete root;
            }
        }

        template <class T>
        tree_node<T>* erase(const T& value, tree_node<T>* root) {
            tree_node<T>* toErase = find(value, root);

            if (toErase) delete erase(toErase, root);
            return root;
        }

        template <typename T>
        tree_node<T>* erase(tree_node<T>* toErase, tree_node<T>*& root) {

            // Case 1: Has 2 children. Copy value of successor node
            // into toErase and del successor (recursively if needed)
            // Works because successor > toErase and thus > toErase's
            // left subtree and is min of toErase's right subtree
            // Relation to toErase's parent unaffected
            if (toErase->left && toErase->right) {
                tree_node<T>* successor = getInorderSuccessor(toErase);
                T temp = toErase->value;
                toErase->value = successor->value;
                successor->value = temp;

                toErase = erase(successor, root);
            }

            // Case 2: Has no child. Nullify root if needed, nullify
            //         ref to toErase form its parent. Del toErase
            else if (!toErase->left && !toErase->right) {
                if (toErase != root) {
                    if (toErase == toErase->parent->left) {
                        toErase->parent->left = nullptr;
                    }
                    else toErase->parent->right = nullptr;
                }
                else root = nullptr;
            }

            // Case 3: Has 1 child. Slot toErase's child into its
            //         place, rewiring toErase->parent. Do not del
            //         child and disconnect child from its descendents
            // Works because only 2 relations (child <-> toErase) and
            // (toErase <-> its parent) affected, but toErase erased 
            else {
                tree_node<T>* child = (toErase->left) ? 
                    toErase->left : toErase->right;
                child->parent = toErase->parent;

                if (toErase != root) {
                    if (toErase == toErase->parent->left) {
                        toErase->parent->left = child;
                    }
                    else toErase->parent->right = child;
                }
                else root = child;
            }

            return toErase;
        }
        
        // Inorder: left subtree -> node -> right subtree
        // Case 1: If right subtree/child exists, successor is
        //         leftmost node down that right subtree
        // Case 2: If right child doesn't exist, node passed
        //         is rightmost down of left child/subtree
        //         of target that is successor to backtrack to
        // Case 3: Rightmost of tree has no successor
        template <typename T>
        tree_node<T>* getInorderSuccessor(const tree_node<T>* node) {
            if (!node) return nullptr;

            // Case 1: Reverse of predecessor's Case 1 
            if (node->right) {
                return min_element(node->right);
            }

            // Case 2: Reverse of predecessor's Case 2
            while (node->parent) {
                if (node == node->parent->right) node = node->parent;
                else return node->parent;
            }

            return nullptr;
        }

        // Case 1: If left child doesn't exist, node passed is
        //         leftmost descendant of right child/subtree of
        //         target that is predecessor to backtrack to
        // Case 2: If left child exists, is rightmost down of left child
        // Case 3: Leftmost of tree has no predecessor
        template <typename T>
        tree_node<T>* getInorderPredecessor(const tree_node<T>* node) {
            if (!node) return nullptr;

            // Case 2
            if (node->left) {
                return max_element(node->left);
            }

            // Case 1
            while (node->parent) {
                if (node == node->parent->left) node = node->parent;
                else return node->parent;
            }

            return nullptr;
        }

        // Use guarantee of BST: if large/smaller exists, it is right/left
        template <typename T>
        tree_node<T>* find(const T& toSeek, tree_node<T>* root) {
            if (!root) return nullptr;
            tree_node<T>* current = root;

            while (true) {
                if (current->right && (current->value < toSeek))
                    current = current->right;

                else if (current->left && (current->value > toSeek))
                    current = current->left;

                else break;
            }

            return current;
        }

        // For min, go as deep leftmost
        template <class T>
        tree_node<T>* min_element(tree_node<T>* root) {
            if (!root) return nullptr;
            tree_node<T>* current = root;

            while (current->left) {
                current = current->left;
            }
            return current;
        }

        // For max, go as deep rightmost
        template <class T>
        tree_node<T>* max_element(tree_node<T>* root) {
            if (!root) return nullptr;
            tree_node<T>* current = root;

            while (current->right) {
                current = current->right;
            }
            return current;
        }
    }
}

// Print inorder traversal recursively
template <class T>
std::ostream& operator<< (std::ostream& os,
    const mesa::tree::tree_node<T>* node) {

    if (node) {
        os << node->left;
        os << node->value << ' ';
        os << node->right;
    }
    return os;
}

#endif

