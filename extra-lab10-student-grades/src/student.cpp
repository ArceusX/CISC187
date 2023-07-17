#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

#include "average.h"
#include "student.h"

void add_student(std::vector<student*>* students, std::istringstream& iss) {
    std::string name;
    unsigned int id;
    int grade;
    student* newStudent = new student();
    if (iss >> name) {
        newStudent->name = name;
        if (iss >> id) {
            newStudent->id = id;
            while (iss >> grade) {
                newStudent->grades.push_back(grade);
            }
            students->push_back(newStudent);
        }
    }
    if (iss.fail()) iss.clear();
}

std::vector<student*> load_classroom() {
  std::string line;
  std::vector<student*> students;
  while (getline(std::cin, line)) {
    std::istringstream stream(line);
    add_student(&students, stream);

    line.clear();
  }
  return students;
}

std::ostream& operator<<(std::ostream& os, const std::vector<student*>& rhs) {
    if (!rhs.empty()) {
        for (const auto& st : rhs) {
            os << st << "\n";
        }
    }
    return os;
}

std::ostream& operator<< (std::ostream& os, const student* rhs) {
    if (rhs != nullptr) {
        os.precision(3);
        os << "Name:\t" << rhs->name << "\tId:\t" << rhs->id << "\tAvg:\t" << std::fixed <<
            (floor(average(rhs->grades) * 100 + 0.5) / 100);
    }
    return os;
}


