#include "lab9.h"

#include <iostream>

int main () {
  using std::cout;

  char orig[6] = "HELLO";

  cout << "original: " << orig << '\n';
  auto uc_count = mesa::count(orig, 'L');
  cout << "'L' count: " << uc_count << '\n';
  mesa::to_lower(orig);
  cout << "lower: " << orig << '\n';

  auto buf = mesa::copy(orig, 6);
  cout << "copy: " << buf << '\n';

  cout << "'L' count: "  << mesa::count(buf, 'L') << '\n';

  delete[] buf;

  int values[] = {2,7,1,-8,2,-8,1,8,2,-8};
  cout << "values = ";
  for (const auto v: values) {
    cout << v << ' ';
  }
  cout << '\n';
  int* min = mesa::min(std::begin(values), std::end(values));
  cout << "min = " << *min << '\t'
       << "index = " << std::distance(std::begin(values), min) << '\n';

  return *min;
}
