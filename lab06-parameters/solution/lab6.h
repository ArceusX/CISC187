#ifndef MESA_CISC187_LAB6_H
#define MESA_CISC187_LAB6_H

#include <cstdint>
#include <vector>

namespace mesa {

  // a POD for a 3 sided polygon, with sides a, b & c.
  // c = the hypotenuse
  struct trigon {
    float a;
    float b;
    float c;
  };

  /**
   * Construct a pythagorean triple from two integers,
   * using Euclid's formula, where m > n > 0.
   */
  trigon make_triple (int16_t m, int16_t n); 

  /**
   * resize a triangle by multiplying each side by a scale factor.
   * @param triangle the trigon to be modified 
   * @param factor the scaling factor applied to the triangle
   *        values < 1.0 reduce the length of each side
   *        factor must be > 0.01
   *        if factor is <= 0.01 the triangle lengths are not changed
   */
  void  scale (trigon& triangle, float factor);

  /**
   * Compute the area of a triangle.
   */
  float  area (const trigon& triangle);

  /**
   * Find the triangle with the smallest area.
   */
  trigon smallest (const std::vector<trigon>& shapes);

} // end namespace mesa

#endif

