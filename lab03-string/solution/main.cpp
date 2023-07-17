#include <iostream>
#include <string>

#include "lab3.h"

using std::string;
using std::cout;

int main() {
  cout << sentence_case("the rain in spain lays mainly on the plain.")
       << '\n'
       << phone_format("5558675309")
       << '\n'
       << name_format("alex stepanov") << std::endl;
  return 0;
}


