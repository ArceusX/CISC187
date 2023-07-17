#pragma once

//
// Functions that offer basic utility
//
// When used together, the functions will prompt the user for input until 
// they enter a valid integer within the given range.
//
// Note: Functions that expect addresses to be passed in as argument are 
// LIKELY TO MODIFY the values found at these addresses
//

#include <string>

using std::string;

// Prompt the user for input and return a valid integer.
int getInt(const string& prompt, const int& maxInt, const string& error);

// Prompt the user for input and return their response as a string.
string getString(const string& prompt);

// Attempt to convert the given string to an int.
//
// If the attempt is successful, the value at the address pointed to by 
// 'result' will be this integer and the function will return true.
//
// Otherwise, the function will return false. Note: the value at the address
// pointed to by 'result' MAY STILL BE MODIFIED.
//
// A custom error message can be included if the attempt is unsuccessful.
bool stringToInt(const string& line, int* result, string error = "");

// Return true if the integer is within 1 and 'maxInt'.
//
// A custom error message can be included if the integer is out of range.
bool checkIntRange(const int& n, const int& maxInt, string error = "");

