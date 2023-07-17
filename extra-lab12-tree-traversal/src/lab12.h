#ifndef MESA_CISC187_TREE
#define MESA_CISC187_TREE

#include <iostream>
#include <queue>

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

    template<typename T>
    void post_order(std::ostream& os, const mesa::tree<T>* tree) {
        if (tree != nullptr) {
            post_order(os, tree->left);
            post_order(os, tree->right);
            os << tree->value << " ";
        }
    }

    template<typename T>
    void in_order(std::ostream& os, const mesa::tree<T>* tree) {
        if (tree != nullptr) {
            in_order(os, tree->left);
            os << tree->value << " ";
            in_order(os, tree->right);
        }
    }

    template<typename T>
    void level_order(std::ostream& os, mesa::tree<T>* tree) {
        if (tree == nullptr) return;

        std::queue<mesa::tree<T>*> q;

        q.push(tree);

        while (!q.empty()) {
            mesa::tree<T>* node = q.front();
            os << node->value << " ";
            q.pop();

            if (node->left != nullptr) {
                q.push(node->left);
            }

            if (node->right != nullptr) {
                q.push(node->right);
            }
        }
    }
}

#endif