#pragma once

// 
// Tree manipulation functions
// Dave Parillo: 20180409
//

#include <iostream>

namespace mesa {

  // a recursive binary tree
  template<class T>
    struct tree {
      T value;
      tree<T>* left = nullptr;
      tree<T>* right = nullptr;
    };


  // make a tree, leaving the chld nodes == nullptr
  template <class T>
    tree<T>* make_tree(T value) {
      auto root = new tree<T>;
      root->value = value;
      return root;
    }

  // make a complete binary tree
  template <class T>
    tree<T>* make_tree(T value, tree<T>* left, tree<T>* right) {
      auto root = make_tree(value);
      root->left  = left;
      root->right = right;
      return root;
    }

  template <class T>
    void delete_tree(tree<T>* root) {
      if (root == nullptr) return;
      delete_tree(root->left);
      delete_tree(root->right);
      delete root;
    }


} // end namespace mesa

// write a tree to an output stream
template <class T>
std::ostream& operator<< (std::ostream& os, const mesa::tree<T>* node) {
  if (node == nullptr) return os;
  os << node->value << ' ';
  os << node->left; 
  os << node->right;
  return os;
}

