//
// Take-away game solution
// Author: Dave Parillo, ID: 123456789
//

#include "game.hpp"

#include <cstring>
#include <locale>
#include <iostream>
#include <string>


static void usage(const char* name) {
  std::cerr << "Usage: " << name << " [-h] [-c] [-p # piles] [-s # stones] \n";
}

static void help (const char* name) {
  usage(name);
  constexpr auto text = R"help_text(
Options:
  -h   Show this text
  -c   Set player two as the computer.  Default = false.
  -p   Manually set the starting number of piles in the game.
  -s   Manually set the starting number of stones in each pile.

       Max values for piles and stones: 99
       Values == 0 are ignored.

)help_text";

  std::cerr << text;
  exit(0);
}

void show_error(const std::string& prompt, const char* name) {
  std::cerr << prompt << '\n';
  usage(name);
  exit(-1);
}

// A command line argument expecting a numeric value is 'valid' if 2 characters or less.
// Simplistic way to prevent overflow
bool is_valid_arg(const char* value) {
  return std::strlen(value) < 2;
}

int main(int argc, char** argv) {
  mesa::option options;
  for (int i=1; i < argc; ++i) {
    if (!std::strcmp(argv[i], "-h")) {
      help(*argv);
    } else if (!std::strcmp(argv[i], "-c")) {
        options.has_ai = true;
    } else if (!std::strcmp(argv[i], "-p")) {
      ++i;
      if (i < argc && is_valid_arg(argv[i])) {
        options.piles = std::atoi(argv[i]);
      } else {
        show_error("Error using '-p' argument: too many or no # piles specified", *argv);
      }
    } else if (!std::strcmp(argv[i], "-s")) {
      ++i;
      if (i < argc && is_valid_arg(argv[i])) {
        options.stones = std::atoi(argv[i]);
      } else {
        show_error("Error using '-s' argument: too many or no # stones specified", *argv);
      }
    } else {
        show_error("Unknown command received!", *argv);
    }
  }

  make_players(options);
  do {
    play(options);
  } while ('y' == std::tolower(get_entry("Play another game? [y/n] ")[0]));

  return 0;
}

