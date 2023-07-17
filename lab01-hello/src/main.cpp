#include <iostream>
#include "echo.h"

int main() {
	for (int i = 0; i < 3; i++) {
		std::cout << echo("Hello, world") << '\n';
	}
  return 0;
}

