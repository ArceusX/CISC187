#include "tree.h"
#include <iostream>
int main(int argc, char* argv[]) {
    auto left = mesa::make_tree(2.71828);
    auto right = mesa::make_tree(1.618);
    auto root = mesa::make_tree(3.14, left, right);
    std::cout << root;
}