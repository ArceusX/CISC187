#include <iostream>
#include <numeric>
#include <stdexcept>
#include <utility>

#include "array.h"

int main()
{
  // init with initializer list
  constexpr size_t size = 3;
  auto data = mesa::array<int, size> {1,2,3};
  std::cout << "print data:\t";
  for (const auto* i = data.begin(); i != data.end(); ++i) {
    std::cout << *i << ' ';
  }
  std::cout << '\n';

  std::cout << "print using range for loop:\t";
  for (const auto& value: data) {
    std::cout << value << ' ';
  }
  std::cout << '\n';

  std::cout << "copy data to y:\t";
  mesa::array<int, size> y = data;
  for (const auto& v: y) {
    std::cout << v << ' ';
  }
  std::cout << '\n';

  mesa::array<int, 0> empty;
  mesa::array<int, size> empty_2;
  std::cout << std::boolalpha 
    << "empty is empty: " << empty.empty() << '\n'
    << "empty_2 is empty: " << empty_2.empty() << '\n';

  // question: why is empty_2 not empty?
  for (const auto& v: empty_2) {
    std::cout << v << ' ';
  }
  std::cout << '\n';

  std::cout << "fill empty 3 with new values:\n";
  constexpr int start_value = 99;
  std::iota(empty_2.begin(), empty_2.end(), start_value);
  for (const auto& v: empty_2) {
    std::cout << v << ' ';
  }
  std::cout << '\n';

  std::cout << "an array of points:\n";
  struct point {
    double x;
    double y;
  };
  const mesa::array<point, 3> p;
  for (const auto& v: p) {
    std::cout << v.x << ',' << v.y << ' ';
  }
  std::cout << '\n';


  return 0;
}

