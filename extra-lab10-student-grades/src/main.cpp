#include <iostream>
#include <fstream>
#include <sstream>

#include "average.h"
#include "student.h"

int main() {
	std::ifstream infile("class.txt");
    std::string line;
    std::vector<student*> students;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        add_student(&students, iss);
    }
    std::cout << students;

    for (const auto& st : students) {
        delete st;
    }
}

