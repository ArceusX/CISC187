#include <cmath>
#include <cstdint>
#include <vector>

#include "lab6.h"

namespace {
  auto zero = mesa::trigon {0,0,0};
} // end anonymous namespace

mesa::trigon mesa::make_triple (int16_t m, int16_t n) {
  if (m <= n || m < 1 || n < 1) {
    return zero;
  }
  float m2 = m*m;
  float n2 = n*n;
  return { m2-n2, 2.f*m*n, m2+n2 };
}

void  mesa::scale (trigon& triangle, float factor) {
  constexpr float near_zero = 0.01;
  if (factor < near_zero) {
    return;
  }
  triangle.a *= factor;
  triangle.b *= factor;
  triangle.c *= factor;
}

float  mesa::area (const trigon& triangle) {
  if (triangle.a > 0 && triangle.b > 0 && triangle.c > 0) {
    // semi-perimeter
    auto s = (triangle.a + triangle.b + triangle.c) * 0.5f;
    // area
    return std::sqrt(s*(s-triangle.a)
                      *(s-triangle.b)
                      *(s-triangle.c));
  }
  return 0.f;
}

mesa::trigon  mesa::smallest (const std::vector<trigon>& shapes) {
  if (shapes.empty()) {
    return zero;
  }
  auto small = shapes.front();
  for (const auto& shape: shapes) {
    // loop accepts that we will compare
    // the first element to itself initially
    if (mesa::area(shape) < mesa::area(small)) {
      small = shape;
    }
  } 
  return small;
}

