#include "list.h"
#include <iostream>

int main() {
    mesa::list<int> test_list{ 1 };
    auto head = test_list.front();
    int expected = 13;
    if (test_list.size() == 1) {
        std::cout << "Size is 1 as expected.\n";
    }
    test_list.insert_after(0, expected);
    if (test_list.front() == head) {
        std::cout << "Head is still 1 for insert_after.\n";
    }
    
    test_list.pop_front();

    if (test_list.front() == expected) {
        std::cout << "Expect the head to now be the value inserted after 1.\n";
    }
}