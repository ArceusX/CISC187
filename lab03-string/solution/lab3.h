#pragma once

#include <string>

// Ensure a string that appears to be a sentence,
// (end in a .) has an upper case first letter
std::string sentence_case(std::string);

// Transform a sequence of 10 digits into 
// standard phone number format: (ddd) ddd-ddd
std::string phone_format(std::string);

// Transform a first name last name pair of strings
// into last name, first initial
std::string name_format(std::string);

