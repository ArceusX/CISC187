#include <iostream>

int main(int argc, char** argv) {
  
  std::cout << "Hello, world!\n";
  // why did I initialize this to 1 instead of 0?
  for (int i=1; i < argc; ++i) {
    std::cout << "Hello, " << argv[i] << '\n';
  }

  return 0;
}

