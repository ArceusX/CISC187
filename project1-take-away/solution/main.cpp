//
// Take-away game solution
// Author: Dave Parillo, ID: 123456789
//

#include <cstring>

#include "options.h"
#include "game.h"

int main(int argc, char** argv) {
  auto options = get_options(argc, argv);

  if (!options.valid) {
	  return -1;
  }
  make_players(options);
  do {
    play(options);
  } while ('y' == std::tolower(get_entry("Play another game? [y/n] ")[0]));

  return 0;
}

