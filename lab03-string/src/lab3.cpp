#include "lab3.h"

#include <vector>
#include <algorithm>
#include <locale>

std::string sentence_case(std::string str) {
	if (!str.empty() && str.back() == '.') {
		str[0] = std::toupper(str[0], std::locale());
	}
	return str;
}

std::string phone_format(std::string str) {

	if (str.length() == 10) {

		std::string::iterator it = str.begin();

		// Check each char is digit
		while (it != str.end()) {
			if (std::isdigit(*it)) ++it;
			else break;
		}

		// If end is reached without encountering non-digit
		if (it == str.end()) {
			str.insert(0, "(");
			str.insert(4, ") ");
			str.insert(str.size() - 4, "-");

			return str;
		}
	}
		
	str.assign("Not a phone number.");
	return str;
}


std::string name_format(std::string name) {
	size_t pos = name.find_first_of(' ');

	// Found ' ' and it is only one
	if (pos != std::string::npos && (pos == name.find_last_of(' '))) {

		// Capitalize first of lastname, leave rest of lastname as is,
		// capitalize first of firstname and leave out rest of firstname
		name = toupper(name[pos + 1], std::locale()) + name.substr(pos + 2) 
			+ ", " + toupper(name[0], std::locale()) + ".";
	}

	return name;
}
