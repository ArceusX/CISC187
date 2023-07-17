#include "array.h"

#include <iostream>
#include <iterator>

int main(int argc, char* argv[]) {
	mesa::array<int, 3> actual{ 1, 2, 3 };
	std::cout << actual.size() << "\n";
	std::cout << "Distance between begin() and end(): " << std::distance(actual.begin(), actual.end()) << "\n";
	actual.print();
}