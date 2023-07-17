#include <iostream>
#include <numeric>
#include <stdexcept>
#include <utility>

#include "bag.h"

int main()
{
  auto x = mesa::bag<int> {1,2,3};
  for (const auto& v: x) {
    std::cout << v << ' ';
  }
  std::cout << '\n';

  for (auto i = 0; i < int(x.size()); ++i) {
    std::cout << x[i] << ',' << x.at(i) << ' ';
  }
  std::cout << "\nmove x into y\n";

  auto y = std::move(x);
  for (auto* i = y.begin(); i != y.end(); ++i) {
    std::cout << *i << ' ';
  }
  std::cout << '\n';


  mesa::bag<int> empty;
  std::cout << std::boolalpha 
    << "empty is empty: " << empty.empty() << '\n'
    << "y is empty: " << y.empty() << '\n';

  std::cout << "new y values:\n";
  std::iota(y.begin(), y.end(),99);
  for (const auto& v: y) {
    std::cout << v << ' ';
  }
  std::cout << '\n';

  struct point {
    double x = 3;
    double y = 5;
  };
  mesa::bag<point> points(5);
  for (const auto& p: points) {
    std::cout << p.x << ',' << p.y << ' ';
  }
  std::cout << '\n';


  try {
    std::cout << y.at(-1) << '\n';
  } catch (const std::exception& e) {
    std::cout << "bad index into 'y': " << e.what() << '\n';
  }
  if (empty == y) {return 2;}
  auto z = empty;
  if (z < y)        {return 1;}
  if (empty == z) {return 3;}

  std::cout << "last line\n";
  return 0;
}

