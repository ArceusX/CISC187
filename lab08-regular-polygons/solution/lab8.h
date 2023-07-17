#ifndef MESA_CISC187_LAB8_H
#define MESA_CISC187_LAB8_H

// 
// Not the only way to solve this lab, but a simple one.
//

#include <cmath>
#include <cstdint>

// define a 'numeric' concept that indicates support for
// addition, multiplication, division, etc.
#define Numeric typename

namespace mesa {

  // ultimate pi day: 3/14/2015 09:26:53!
  constexpr double pi = 3.141592653;

  template <Numeric T>
    constexpr
    bool polygon_valid (const T length, int16_t num_sides) {
      static_assert(std::is_arithmetic<T>::value,
          "length must be a numeric type");
      return length > 0 && num_sides > 2;
    }

  // for shapes with only 1 parameter, a circle radius is assumed
  template <Numeric T>
    constexpr double area(const T radius) {
      static_assert(std::is_arithmetic<T>::value,
          "area must be a numeric type");
      return radius > 0? pi * radius * radius: 0;
    }

  template <Numeric T>
    double perimeter(const T length, int16_t num_sides) {
      if (polygon_valid(length, num_sides)) {
        return length * num_sides;
      }
      return 0;
    }

  template <Numeric T, int16_t num_sides>
    double apothem(const T length) {
      if (polygon_valid(length, num_sides)) {
        return 0.5 * length / std::tan(pi/num_sides);
      }
      return 0;
    }

  template <Numeric T, int16_t num_sides>
    auto area(const T length) -> decltype(length * 1.0f) {
      return (apothem<T, num_sides>(length) * 
              perimeter(length, num_sides)) * 0.5;
    }

} // end namespace mesa

#endif

