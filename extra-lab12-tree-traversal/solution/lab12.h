#pragma once

// 
// Tree manipulation functions
// Dave Parillo: 20180409
//

#include <iostream>
#include <queue>

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
      auto root = new tree<T>;
      root->value = value;
      root->left  = left;
      root->right = right;
      return root;
    }

  // write a tree to an output stream
  // using preorder traversal
  template <class T>
    void post_order(std::ostream& os, const tree<T>* node) {
      if (node == nullptr) return;
      post_order(os, node->left); 
      post_order(os, node->right); 
      os << node->value << ' ';
    }


  // write a tree to an output stream
  // using inorder traversal
  template <class T>
    void in_order(std::ostream& os, const tree<T>* node) {
      if (node == nullptr) return;
      in_order(os, node->left); 
      os << node->value << ' ';
      in_order(os, node->right); 
    }


  // write a tree to an output stream
  // using level order traversal
  template <class T>
    void level_order(std::ostream& os, tree<T>* node) {
      if (node == nullptr) return;
      std::queue<tree<T>*> q;
      q.push(node);
      while (!q.empty()) {
        auto tmp = q.front();
        os << tmp->value << ' ';
        q.pop();
        if(tmp->left)  q.push(tmp->left);
        if(tmp->right) q.push(tmp->right);
      }
    }


} // end namespace mesa

// write a tree to an output stream
// using preorder traversal
template <class T>
std::ostream& operator<< (std::ostream& os, const mesa::tree<T>* node) {
  if (node == nullptr) return os;
  os << node->value << ' ';
  os << node->left; 
  os << node->right;
  return os;
}

