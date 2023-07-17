#include <iostream>
#include <numeric>
#include <stdexcept>
#include <utility>

#include "array.h"

int main()
{
  using std::cout;
  // init with initializer list
  constexpr size_t size = 3;
  auto data = mesa::array<int, size> {1,2,3};
  cout << "print data:\t";
  for (auto* i = data.begin(); i != data.end(); ++i) {
    cout << *i << ' ';
  }
  cout << '\n';

  cout << "print using range for loop:\t";
  for (const auto& value: data) {
    cout << value << ' ';
  }
  cout << '\n';

  cout << "print using raw for loop:\t";
  for (auto i = 0; i < int(data.size()); ++i) {
    cout << data[i] << ' ';
  }
  cout << '\n';

  cout << "print using raw for loop range checked:\t";
  for (auto i = 0; i < int(data.size()); ++i) {
    cout << data.at(i) << ' ';
  }
  cout << '\n';

  try {
    constexpr int error_value = -1;
    cout << data.at(error_value) << ' ';
  } catch (const std::out_of_range& e) {
    cout << "bad index into 'data': " << e.what() << '\n';
  }


  auto x = data;
  auto y = data;
  mesa::array<int, size> empty;
  cout << std::boolalpha 
    << "boolean assortment: " << '\n'
    << "x < y: " << (x < y)  << '\n'
    << "x > y: " << (x > y)  << '\n'
    << "empty == y: " << (empty == y)  << '\n'
    << "empty != y: " << (empty != y)  << '\n'
    << "empty <= y: " << (empty <= y)  << '\n'
    << "empty >= y: " << (empty >= y)  << '\n';

  return 0;
}

