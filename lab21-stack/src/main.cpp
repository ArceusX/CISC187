#include "stack.h"

#include <algorithm>

int main() {
	mesa::stack<int> stack2({ 0, 1, 2 });
	mesa::stack<int> stack1;
	stack1 = std::move(stack2);

	int gh = 13;
}