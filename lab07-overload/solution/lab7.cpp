#include <ostream>
#include "lab7.h"

std::ostream& operator<<(std::ostream& os, const mesa::point& p)
{
  return os << '[' << p.x << ',' << p.y << ']';
}

