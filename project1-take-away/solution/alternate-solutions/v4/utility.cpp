#include "utility.h"

#include <iostream>
#include <string>
#include <sstream>

using std::string;

int getInt(const string& prompt, const int& maxInt, const string& error) {
   int result;
   while(true) {
      string userInput = getString(prompt);
      if (!stringToInt(userInput, &result, error))
         continue; //not a valid input
      if (checkIntRange(result, maxInt, error))
         break; //valid integer and in range
   }
   return result;
}

string getString(const string& prompt) {
   string line;
   do { 
      std::cout << prompt;
      std::getline(std::cin, line);
   } while (line.empty());
   return line;
}

bool stringToInt(const string& line, int* result, string error) {
   std::istringstream buf(line);
   if(buf >> *result) {
      // check for any extra input and reject input if found
      char junk;
      if (!(buf >> junk))
         return true;
   }
   if (!error.empty())
      std::cerr << error << '\n';
   return false;
}

bool checkIntRange(const int& n, const int& maxInt, string error) {
   //function assumes the minimum number n can be is 1; 
   if (n < 1 || n > maxInt) {
      if (!error.empty())
         std::cerr << error << "\n";
      std::cerr << "   Enter a number between 1 and " << maxInt << ".\n";
      return false;
   }
   return true;
}

