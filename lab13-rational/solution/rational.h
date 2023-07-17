#ifndef MESA_LAB13_RATIONAL_H
#define MESA_LAB13_RATIONAL_H

#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include <type_traits>

#define IntegralType typename

/**
 * A value class for Rational numbers. 
 *
 * A 'rational number' is one that can be represented as the 
 * ratio of two integers.
 */
template <IntegralType T>
class rational {
  static_assert(std::is_integral<T>::value,
      "Integral required.");
  public:
    rational() = default;
    explicit rational(T n, T d = 1)
      : n{n}
      , d{d} 
    { }

    T numerator()   const {return n;}
    T denominator() const {return d;}

    double to_double() const {
      if (d==0) return std::numeric_limits<double>::infinity();
      return double(n) / d;
    }
    // operator double() const
    // is more idiomatic than 'to_double'
    explicit operator double() const {
      return to_double();
    }
    explicit operator std::string () const {
      if (n == 0) {return "0";}
      if (d == 0) {return "inf";}
      if (n == d) {return "1";}
      std::stringstream ss;
      ss << n << '/' << d;
      return ss.str();
    }

  private:
    T n = 0;
    T d = 1;
};

//
// Non-member functions
//

// This is how I typically implement non-member operator overloads.
// The function is not a friend of the class and has no access to private data
// For a class template, a version of this function will be written
// for each type T
template <IntegralType T>
std::ostream& operator<<(std::ostream& os, const rational<T>& rhs) {
    return os << std::string(rhs);
}
#endif


