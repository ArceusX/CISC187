#include <vector>

#include "average.h"

double average (const std::vector<int>& grades) {
  // Your code here.
  // return the average of all the grades in the vector
  auto sum = 0.0;
  if (grades.empty()) return sum;
  for (const auto& val: grades) {
    sum += val;
  }
  return sum / double(grades.size());
}

