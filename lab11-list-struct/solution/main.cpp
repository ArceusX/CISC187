#include <iostream>

#include "list.h"

int main() {

  { // scope to force destruction before main exits
    list* nums = new list(5);
    nums = nums->insert(10);
    nums = nums->insert(20);
    nums = nums->insert(30);
    std::cout << "insert:\n";
    std::cout << nums << '\n';
    nums = erase(nums);
    nums = erase(nums);
    std::cout << "after erase:\n";
    std::cout << nums << '\n';
  }

  return 0;
}

