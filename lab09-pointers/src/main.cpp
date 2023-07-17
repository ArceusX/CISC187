#include "lab9.h"
#include <iostream>
int main(int argc, char* argv[]) {
    char Triet[6] = "Triet";

    auto actual = mesa::copy(Triet, strlen(Triet));
    std::cout << Triet;
    delete[] actual;
}