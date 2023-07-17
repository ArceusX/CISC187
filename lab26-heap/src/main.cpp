
#include <iostream>
#include <vector>

#include "binary_heap.h"

int main()
{
  std::vector<int> v = {14,19,16,19,8,21,26,65,32,31,14};
  binary_heap<int> h{v};

  std::cout << "front:\t" << h.front();

  while (!h.empty()) {
    std::cout << "\nheap:\t(" << h.size() << ")\n";
    std::cout << h;
    h.pop();
  }

  std::cout << "\nempty heap:\t(" << h.size() << ")\n";
  std::cout << h;

  h.insert(9);
  h.insert(8);
  h.insert(7);
  h.insert(6);
  h.insert(5);
  h.insert(4);
  h.insert(3);
  h.insert(2);
  h.insert(-1);
  h.insert(-2);
  h.insert(-3);

  std::cout << "\nafter inserts:\t(" << h.size() << ")\n";
  std::cout << h;

}
