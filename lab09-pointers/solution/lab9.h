#ifndef MESA_LAB9_H
#define MESA_LAB9_H

#include <cstddef>

namespace mesa {

  // Transform a character array, replace all upper case
  // characters with lower case.
  void to_lower(char* s);

  // Copy a C-string to a new array on the free store
  char* copy(const char* source, size_t count);


  // Count the occurrences of value in data
  size_t count(const char* data, char value);

  template<class Pointer>
    Pointer min (Pointer begin, Pointer end)
    {
      if (begin == end) {
        return end;
      }
      Pointer smallest = begin;
      ++begin;
      for (; begin != end; ++begin) {
        if (*begin < *smallest) {
          smallest = begin;
        }
      }
      return smallest;
    }

} // end namespace mesa

#endif

