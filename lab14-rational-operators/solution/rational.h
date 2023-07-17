#ifndef MESA_LAB16_RATIONAL_H
#define MESA_LAB16_RATIONAL_H

#include <cmath>
#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include <type_traits>

#define IntegralType typename

/**
 * A value class for Rational numbers. 
 *
 * A 'rational number' is one that can be represented as the ratio of two integers.
 *
 * @note
 *  This class is not yet 'regular', because we have not added move semantics.
 *  We get swap automatically, however.
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
    explicit operator double() const {
      return to_double();
    }
    operator std::string () const; 

    rational<T>& operator= (const rational&);
    rational<T>& operator+=(const rational&);
    rational<T>& operator-=(const rational&);
    rational<T>& operator*=(const rational&);
    rational<T>& operator/=(const rational&);

  private:
    T n = 0;
    T d = 1;
};

//
// Member functions
//

template <IntegralType T>
rational<T>::operator std::string () const {
  if (n == 0) return "0";
  if (d == 0) return "inf";
  if (n == d) return "1";
  std::stringstream ss;
  ss << n << '/' << d;
  return ss.str();
}

template <IntegralType T>
inline
rational<T>& rational<T>::operator=(const rational<T>& other) {
  n = other.n;
  d = other.d;
  return *this;
}

template <IntegralType T>
inline
rational<T>& rational<T>::operator*=(const rational<T>& other) {
  n *= other.n;
  d *= other.d;
  return *this;
}

template <IntegralType T>
inline
rational<T>& rational<T>::operator+=(const rational<T>& other) {
  auto ad = n * other.d;
  auto bc = d * other.n;
  d =  d * other.d;
  n = ad + bc;
  return *this;
}

template <IntegralType T>
inline
rational<T>& rational<T>::operator-=(const rational<T>& other) {
  auto ad = n * other.d;
  auto bc = d * other.n;
  d =  d * other.d;
  n = ad - bc;
  return *this;
}

template <IntegralType T>
inline
rational<T>& rational<T>::operator/=(const rational<T>& other) {
  n *= other.d;
  d *= other.n;
  return *this;
}

//
// Non-member functions
//

// The rational numbers are equality comparable
template <IntegralType T>
inline
bool operator==(const rational<T>& lhs, const rational<T>& rhs) {
  auto ad = lhs.numerator()   * rhs.denominator();
  auto bc = lhs.denominator() * rhs.numerator();
  return ad == bc;
}

// The rational numbers are totally ordered
template <IntegralType T>
inline
bool operator< (const rational<T>& lhs, const rational<T>& rhs) {
  auto ad = lhs.numerator()   * rhs.denominator();
  auto bc = lhs.denominator() * rhs.numerator();
  return ad < bc;
}

template <IntegralType T>
inline
bool operator!=(const rational<T>& lhs, const rational<T>& rhs) {
  return !(lhs == rhs);
}

template <IntegralType T>
inline
bool operator> (const rational<T>& lhs, const rational<T>& rhs) {
  return  rhs < lhs;
}

template <IntegralType T>
inline
bool operator<=(const rational<T>& lhs, const rational<T>& rhs) {
  return !(lhs > rhs);
}

template <IntegralType T>
inline
bool operator>=(const rational<T>& lhs, const rational<T>& rhs) {
  return !(lhs < rhs);
}

template <IntegralType T>
inline
rational<T> operator+(rational<T> lhs, const rational<T>& rhs) {
  lhs += rhs;
  return lhs;
}

template <IntegralType T>
inline
rational<T> operator-(rational<T> lhs, const rational<T>& rhs) {
  lhs -= rhs;
  return lhs;
}

template <IntegralType T>
inline
rational<T> operator*(rational<T> lhs, const rational<T>& rhs) {
  lhs *= rhs;
  return lhs;
}

template <IntegralType T>
inline
rational<T> operator/(rational<T> lhs, const rational<T>& rhs) {
  lhs /= rhs;
  return lhs;
}

template <IntegralType T>
inline
std::ostream& operator<<(std::ostream& os, const rational<T>& num) {
  return os << std::string(num);
}

#endif


