#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "average.h"
#include "student.h"

void add_student(std::vector<student*>* students, std::istringstream& iss) {
  // Your code here. 
  // Implement a function to add one student and their grades from the input stream to the vector
  student* s = new student;
  iss >> s->name >> s->id;
  if (s->name.empty()) {
    delete s;
    return;
  }
  for (int grade; iss >> grade; ) {
    s->grades.push_back(grade);
  }
  students->push_back(s);
}

std::vector<student*> load_classroom() {
  std::string line;
  // Your code here. Init a new classroom
  std::vector<student*> classroom;
  while (getline(std::cin, line)) {
    std::istringstream stream(line);
    // Your code here. add students to the classroom
    add_student(&classroom, stream);
    line.clear();
  }
  // Your code here. Return your classroom
  return classroom;
}

std::ostream& operator<< (std::ostream& os, const std::vector<student*>& rhs) {
  // Your code here. Implement a function to print all students
  for (student* s: rhs) {
    os << s;
  }
  return os;
}

std::ostream& operator<< (std::ostream& os, const student* rhs) {
  // Your code here. Implement a function to print one student
  return os << "Name:\t" << rhs->name << '\t'
            << "Id:\t"   << rhs->id << '\t'
            << std::setprecision(4)
            << "Avg:\t"  << average(rhs->grades) << std::endl;
}


