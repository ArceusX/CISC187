#include <iostream>
#include "lab10.h"

int main()
{
  auto left_child = mesa::make_tree<int> (1);
  auto right_child = mesa::make_tree<int> (5);
  auto tree = mesa::make_tree<int> (3, left_child, right_child);

  left_child->left = mesa::make_tree<int> (4);
  left_child->right = mesa::make_tree<int> (1);
  right_child->left = mesa::make_tree<int> (9);

  std::cout << tree << '\n';

  mesa::delete_tree(tree);
  return 0;
}

