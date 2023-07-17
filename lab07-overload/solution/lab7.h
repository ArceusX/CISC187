#ifndef MESA_LAB7_H
#define MESA_LAB7_H

#include <iosfwd>

namespace mesa {

  struct point {
    int x;
    int y;
  };

  template <typename T>
    constexpr
    T abs(const T value) {
      return value < 0? -value: value;
    }
} // end namespace mesa


std::ostream& operator<<(std::ostream&, const mesa::point&);

inline
bool operator==(const mesa::point& lhs, const mesa::point& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}


inline
bool operator!=(const mesa::point& lhs, const mesa::point& rhs)
{
  return !(lhs == rhs);
}

#endif

