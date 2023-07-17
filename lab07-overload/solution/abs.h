#ifndef MESA_LAB7_ABS_H
#define MESA_LAB7_ABS_H

#include <cstdint>

// functions to return the absolute value of a number
// This is the minimum number of overloads to work for any fundamental type.
// Adding more might make it marginally more efficient for some compilers


namespace mesa {

  // seems redundant, but included so that any type provided will compile
  constexpr
  unsigned abs (const unsigned a) {
    return a;
  }

  constexpr
  unsigned char abs (const unsigned char a) {
    return a;
  }

  constexpr
  int abs (const int a) {
    return a<0? -a: a;
  }

  constexpr
  long abs (const long a) {
    return a<0? -a: a;
  }

  constexpr
  double abs (const double a) {
    return a<0? -a: a;
  }


  // for types that are at least 64 bit
  // see http://en.cppreference.com/w/cpp/language/types

  constexpr
  long long abs (const long long a) {
    return a<0? -a: a;
  }

  constexpr
  long double abs (const long double a) {
    return a<0? -a: a;
  }

  constexpr
  unsigned long abs (const unsigned long a) {
    return a;
  }

} // end namespace mesa

#endif

