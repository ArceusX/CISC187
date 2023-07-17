#pragma once

#include <iosfwd>
#include <string>
#include <vector>

/**
 * A POD for a single student and their grades.
 */
struct student {
  std::string name;
  unsigned id;
  std::vector<int> grades; 
};

// Add a new student from a input string stream to the list of students
void add_student(std::vector<student*>*, std::istringstream&);

// load an entire classroom of students and return it
std::vector<student*> load_classroom(); 

// write an entire classroom to an output stream
std::ostream& operator<< (std::ostream&, const std::vector<student*>&); 

// write an one student to an output stream
std::ostream& operator<< (std::ostream&, const student*);
