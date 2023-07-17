#ifndef MESA_LAB15_FRIEND2_H
#define MESA_LAB15_FRIEND2_H

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
    rational() : n{0}, d{1} {}
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
      if (n == 0) return "0";
      if (d == 0) return "inf";
      if (n == d) return "1";
      std::stringstream ss;
      ss << n << '/' << d;
      return ss.str();
    }

  private:
    T n;
    T d;
    // In order to use template parameters in a friend,
    // you have to use a different type parameter.
    // If we reuse <T> here, we will effectively define a new variable 'T'
    // that 'shadows' the T defined everywhere else in this class.
    // The code will compile, but will fail to link when a call is attempted.
    //
    // This is a very 'open-ended' template instantiation.
    // We are effectively saying ALL instantiations of this template are my friend
    // Example, this function can access rational<int> rational<foo>, etc.
    // regardless of what <T> is.
    template <typename U> 
    friend
    std::ostream& operator<<(std::ostream&, const rational<U>&);
};

//
// Non-member functions
//

template <IntegralType T>
std::ostream& operator<<(std::ostream& os, const rational<T>& rhs) {
    if (rhs.n == 0)     return os << '0';
    if (rhs.d == 0)     return os << "inf";
    if (rhs.n == rhs.d) return os << '1';
    return os << rhs.n << '/' << rhs.d;
}

#endif


