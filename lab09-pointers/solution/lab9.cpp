#include "lab9.h"

#include <cstddef>
#include <cstring>

void mesa::to_lower(char* s) {
  // determine the amount to add to an uppercase char to make it lower case
  constexpr char char_offset = 'a'-'A';

  // could have been a for loop instead . . .
  // for (int i = 0; s[i]; ++s) {
  // while(*s) . . . is commonly seen, but an implicit conversion
  while(*s != 0) {
    if (*s >= 'A' && *s <= 'Z') {
      *s += char_offset;
    }
    ++s;
  }
}

char* mesa::copy(const char* source, const size_t count) {
  // if (!source) . . . is commonly seen, but an implicit conversion
  if (source == nullptr) {
    return nullptr;
  }
  char* dest = new char[count+1];
  for (size_t i = 0; i < count; ++i) {
    dest[i] = source[i];
  }
  dest[count] = '\0';
  return dest;
}


size_t mesa::count(const char* data, const char value) {
  auto count = 0u;
  if (data == nullptr) {
    return count;
  }
  while(*data != 0) {
    if (*data == value) {
      ++count;
    }
    ++data;
  }
  return count;
}

