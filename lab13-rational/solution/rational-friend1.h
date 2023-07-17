#ifndef MESA_LAB15_FRIEND1_H
#define MESA_LAB15_FRIEND1_H

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
      if (n == 0) return "0";
      if (d == 0) return "inf";
      if (n == d) return "1";
      std::stringstream ss;
      ss << n << '/' << d;
      return ss.str();
    }

  private:
    T n = 1;
    T d = 0;
    // The simplest way to implement operator<< as a friend
    // is to define the function inline
    // Note the second argument is NOT a template
    // The compiler will create a non-member, non-templated function 
    // for each instantiation of the class template
    //
    // Also note this is in the 'private section'.
    // Friends can never be private because they are not members.
    // The access modifer does not apply to a friend.
    friend
    std::ostream& operator<<(std::ostream& os, const rational& rhs) {
        return os << std::string(rhs);
    }

};

#endif


