
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "lab4.h"

using std::vector;

// atoi does not report errors
// std::strtol is an alternative that does
vector<int> make_vector(int argc, const char* argv[])
{
  vector<int> numbers;
  char* end = nullptr;
  for (int i = 0; i < argc; ++i) {
    const long value = std::strtol(argv[i], &end, 10);
    const bool range_error = errno == ERANGE;
    if (!range_error) {
      numbers.push_back(value);
    }
  }
  return numbers;
}

int add(int argc, const char* argv[]) {
  int sum = 0;
  if (argc > 0) {
    auto v = make_vector(argc, argv);
    for (const auto& x: v) {
      sum += x;
    }
  }
  return sum;
}

double mean(int argc, const char* argv[]) {
  return argc==0? 0: add(argc, argv) / double(argc);
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

// private swap function used in the alternate reverse below
namespace {
  void swap(int& x, int& y) {
    int tmp = x;
    x = y;
    y = tmp;
  }
}

// swapping values in place requires only looping
// though half the vector
vector<int> reverse(vector<int> values) {
  int sz = values.size();
  for (int i = 0; i < sz / 2; ++i) {
    swap(values[i], values[sz-i-1]);
  }

  return values;
}

