#include "bstree.h"
#include "tree_node.h"

#include <iostream>

int main(int argc, char* argv[]) {
	using Node = mesa::tree::tree_node<int>;
	mesa::bstree<int> tree(
		{ 25, 20, 36, 10, 22, 5, 12, 30, 40, 28, 38, 48 });
	tree.erase(36);
}

