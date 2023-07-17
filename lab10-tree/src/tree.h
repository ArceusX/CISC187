#ifndef MESA_CISC187_TREE
#define MESA_CISC187_TREE

#include <iostream>

namespace mesa {

    template<typename T = double>
    struct tree {
        T value;
        tree<T>* left;
        tree<T>* right;

        tree() { left = nullptr; right = nullptr; }

        ~tree() {
            delete left;
            delete right;
        }
    };

    template<typename T>
    tree<T>* make_tree(T value, tree<T>* left = nullptr, tree<T>* right = nullptr) {
        tree<T>* t = new tree<T>();
        t->value = value;
        t->left = left;
        t->right = right;
        return t;
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const mesa::tree<T>* tree) {
    if (tree != nullptr) {
        os << tree->value << " " << tree->left << tree->right;
    }
    return os;
}

#endif