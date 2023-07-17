//
// Take-away game solution
// Author: Dave Parillo, ID: 123456789
//
#ifndef CISC187_TAKE_AWAY_OPTIONS_H
#define CISC187_TAKE_AWAY_OPTIONS_H

#include <cstring>
#include <iostream>
#include <locale>
#include <string>

namespace mesa {
  // holds processed command line arguments.
  // the bool valid is used to flag that
  // all command line argument porcessing is ok
  struct option {
    bool valid = true;
    bool has_ai = false;  // is the computer a player?
    int32_t piles = 0;   // number of heaps in game
    int32_t stones = 0;  // number of stones in each heap
  };
}  // end namespace mesa


std::string usage(const char* name);

std::string help (const char* name);

std::string show_error(const std::string& prompt, const char* name);

/**
 * Return true if a cstring is a valid numeric
 * value (for the purposes of this game).
 */
bool is_valid_arg(const char* value);

mesa::option get_options(int argc, char** argv);

#endif

