//
// Take-away game solution
// Author: Dave Parillo, ID: 123456789
//

#include "options.h"

#include <cstring>
#include <locale>
#include <iostream>
#include <string>

using std::string;

string usage(const char* name) {
	string msg = "Usage: ";
	return msg.append(name).append(" [-h] [-c] [-p # piles] [-s # stones]\n");
}

string help (const char* name) {
  auto msg = usage(name);
  constexpr auto text = R"help_text(
Options:
  -h   Show this text
  -c   Set player two as the computer.  Default = false.
  -p   Manually set the starting number of piles in the game.
  -s   Manually set the starting number of stones in each pile.

       Max values for piles and stones: 99
       Min values for piles and stones: 1

)help_text";

  return msg.append(text);
}

string show_error(const string& prompt, const char* name) {
	string msg = prompt;
	return msg.append("\n") + usage(name);
}

// A command line argument expecting a numeric value is 'valid' if 2 characters or less.
// Simplistic way to prevent overflow
bool is_valid_arg(const char* value) {
	return std::strlen(value) < 2 && std::atoi(value) > 0;
}

mesa::option get_options (int argc, char** argv) {
	using std::strcmp;
	using std::atoi;
	mesa::option options;
	for (int i=1; i < argc; ++i) {
    if (!options.valid) {
      break;
    }
		if (strncmp(argv[i], "-h", 2) == 0) {
			std::cerr << help(*argv);
			options.valid = false;
		} else if (strncmp(argv[i], "-c", 2) == 0) {
			options.has_ai = true;
			options.valid = true;
		} else if (strncmp(argv[i], "-p", 2) == 0) {
			++i;
			if (i < argc && is_valid_arg(argv[i])) {
				options.piles = atoi(argv[i]);
			} else {
				std::cerr << 
					show_error("Error using '-p' argument: too many or no # piles specified", *argv);
				options.valid = false;
			}
		} else if (strncmp(argv[i], "-s", 2) == 0) {
			++i;
			if (i < argc && is_valid_arg(argv[i])) {
				options.stones = atoi(argv[i]);
			} else {
				std::cerr << 
          show_error("Error using '-s' argument: too many or no # stones specified", *argv);
				options.valid = false;
			}
		} else {
			std::cerr << 
				show_error("Unknown command received!", *argv);
			options.valid = false;
		}
	}

	return options;
}

