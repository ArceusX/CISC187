//
// An alternative solution that tries to generally avoid
// some of the convenience functions the string class offers.
//
// Consequently, it needs a lot of loops and more code
//

#include <string>

#include "lab3.h"

std::string sentence_case(std::string text) {
  if (text.back() == '.') {
    text[0] = std::toupper(text[0]); 
  }
  return text;
}

std::string phone_format(std::string digits) {
  const std::string error = "Not a phone number.";
  if (digits.size() != 10) return error;
 
  // if len 10 and all digits: phone number
  bool is_phone_number = true;
  for (const char& c: digits) {
    if (! std::isdigit(c)) {
      is_phone_number = false;
      break;
    }
  }
  if (is_phone_number) {
    digits.insert(0, "(");
    digits.insert(4, ")");
    digits.insert(5, 1, ' ');       // space after area code
    digits.insert(digits.size()-4, 1, '-');
  } else {
    return error;
  }
  return digits;
}

std::string name_format(std::string name) {
  int space_count = 0;
  // a range for loop would be better here
  for (unsigned j = 0; j < name.size(); ++j) {
    if (name[j] == ' ') {
      ++space_count;
    }
  }
  if (space_count == 1) {
    auto pos = name.find_first_of(' ');
    std::string last_name;
    // loop explicitly setting unsigned as type
    for (unsigned j = pos+1; j < name.size(); ++j) {
      last_name += std::string(1, name[j]);
    }
    last_name[0]              = std::toupper(last_name[0]);
    std::string first_initial = std::string(1, name[0]);
    first_initial[0] = std::toupper(first_initial[0]);
    name = last_name;
    name += ", ";
    name += first_initial;
    name += ".";
  }
  return name;
}


