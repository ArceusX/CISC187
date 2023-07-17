#include <locale>
#include <string>

#include "lab3.h"

std::string sentence_case(std::string text) {
  if (text.back() == '.') {
    char& front = text.front();
    front = std::toupper(front, std::locale()); 
  }
  return text;
}

std::string phone_format(std::string digits) {
  const std::string error = "Not a phone number.";
  if (digits.size() != 10) return error;
  if (digits.find_last_not_of("0123456789") == std::string::npos) {
    digits.insert(0, 1, '(');  // insert 1 char
    digits.insert(4, ")");     // insert char* instead
    digits.insert(5, 1, ' ');
    digits.insert(digits.size()-4, 1, '-');
  } else {
    return error;
  }
  return digits;
}

std::string name_format(std::string name) {
    auto pos = name.find_first_of(' ');
    if (pos != std::string::npos && pos == name.find_last_of(' ')) {
        // there is exactly 1 space in name
        auto lastName = name.substr(pos + 1);
        char& front = lastName.front();
        front = std::toupper(front, std::locale());
        auto ch = std::toupper(name[0], std::locale());
        name = lastName;
        name.append(", ").append(1, ch).append(1, '.');
    }
    return name;
}
