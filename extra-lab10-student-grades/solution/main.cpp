#include <iostream>

#include "average.h"
#include "student.h"

int main() {

  // Your code here. 
  // get a classroom from the load_classroom function
  // and print the classroom
  auto classroom = load_classroom();
  std::cout << classroom;

  // Your code here.  Clean up all pointers on the heap
  for (student* s: classroom) {
    delete s;
  }

}

