#include <iostream>
#include <utility>

#include "list.h"


list* list::insert(int new_value)
{
  list* node = new list(new_value);
  node->next = this;           // this object comes after new value
  return node;
}

list* erase(list* node)
{
  if (node == nullptr) {
    return nullptr;
  }
  list* tmp = node->next;
  delete node;
  return tmp;
}

std::ostream& operator<<(std::ostream& os, const list* rhs)
{
  while (rhs != nullptr) {
    os << rhs->value << ' ';
    rhs = rhs->next;
  }
  return os;
}


