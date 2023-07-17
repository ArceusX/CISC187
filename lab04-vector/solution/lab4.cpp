
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "lab4.h"

using std::vector;

vector<int> make_vector(int argc, const char* argv[])
{
  // we know how big the vector needs to be
  // pre-allocating the size is more efficient
  // than using 'push_back' in a loop
  vector<int> numbers(argc);
  for (int i = 0; i < argc; ++i) {
    numbers[i] = std::atoi(argv[i]);
  }
  return numbers;
}

int add(int argc, const char* argv[]) {
  auto v = make_vector(argc, argv);
  int sum = 0;
  for (const auto& x: v) {
    sum += x;
  }
  return sum;
}

double mean(int argc, const char* argv[]) {
  if (argc == 0) {
    return 0;
  }
  return add(argc, argv) / double(argc);
}

vector<int> odd(const vector<int>& values) {
  vector<int> v;
  for (const auto& x: values) {
    if (x % 2 == 1) {
      v.push_back(x);
    }
  }
  return v;
}

vector<int> reverse(vector<int> values) {
  // most people will implement a solution like this
  // Aurguably, the simplest thing that works, but inefficient
  vector<int> v;
  for (auto sz=values.size(); sz > 0; --sz) {
    v.push_back(values[sz-1]);
  }
  return v;
}


