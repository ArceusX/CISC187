#include <iostream>
#include "lab12.h"

int main()
{
  using std::cout;

  auto left_child = mesa::make_tree('B');
  auto right_child = mesa::make_tree('C');
  auto tree = mesa::make_tree('A', left_child, right_child);

  left_child->left = mesa::make_tree('D');
  left_child->right = mesa::make_tree('E');
  right_child->left = mesa::make_tree('F');
  right_child->right = mesa::make_tree('G');

  cout << "preorder:\n";
  cout << tree << '\n';

  cout << "postorder:\n";
  mesa::post_order(cout, tree);

  cout << "\ninorder:\n";
  mesa::in_order(cout, tree);

  cout << "\nlevel order:\n";
  mesa::level_order(cout, tree);
  cout << '\n';


  return tree->value;
}

