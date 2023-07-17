#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>

// a program that swaps two values and increments each swapped value by one
int main(int argc, char** argv) {
  int a = 10;
  int b = 20;
  for (int i=1; i < argc; ++i) {
    if (std::strcmp(argv[i], "-a") == 0) {
      ++i;
      if (i < argc) {
        a = std::atoi(argv[i]);
      } else {
        std::cerr << "Error using '-a' argument: no value provided\n";
      }
    } else if (std::strcmp(argv[i], "-b") == 0) {
      ++i;
      if (i < argc) {
        b = std::atoi(argv[i]);
      } else {
        std::cerr << "Error using '-b' argument: no value provided\n";
      }
    } else {
      std::cerr << "Unrecognized argument. Using defaults.\n";
      std::cerr << "Usage: " << argv[0] 
        << " [-a an_int] [-b an_int]\n";
    }
  }
  std::cout << "original values:\n";
  std::cout << "a: " << a << ", ";
  std::cout << "b: " << b << '\n';

  // make temp copies before call
  int x = a;
  int y = b;

  std::swap (++a, ++b);

  std::cout << "\nafter swap and add:\n";
  std::cout << "a: " << a << ", ";
  std::cout << "b: " << b << std::endl;

  // validate a and b
  assert (a == y+1);
  assert (b == x+1);
  
  return 0;
}

