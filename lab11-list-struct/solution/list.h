#ifndef MESA_CISC187_LIST_H
#define MESA_CISC187_LIST_H

#include <iosfwd>

// A simple linked list
struct list {
    int value = 0; 
    list* next = nullptr;

    explicit list(const int value = 0)
        : value{value} 
    { }

    ~list()
    {
      while (next != nullptr)
      {
        next = erase(next);
      }
    }
    // 
    // Insert a new value before the current element.
    // Return a pointer to the new list element
    list* insert(int new_value);
};

// remove the provided element from list
// Return a pointer to the next element
list* erase(list* node);

// extract the right hand side operator to an output stream
std::ostream& operator<<(std::ostream& os, const list* rhs);

#endif

