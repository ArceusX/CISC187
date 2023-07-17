#pragma once

//
// Display usage message and explain command line argument options.
//
// NOTE: I have added a command line argument [-t] for running doctests and
// all options intended for the doctest MUST be prefixed with --dt. 
//

#include <iostream>

// Display help options and exit.
void displayHelp() {
   std::cerr << "Usage: ./take-away [-h] [-c] [-p # piles] [-s # stones] "
             << "[-t [--dt-option]]\n\n";

   std::cerr << "Options:\n"
             << "  -h Show this text.\n"
             << "  -c Make player two the computer. Default is false.\n"
             << "  -p Manually set the starting number of piles "
             << "in the game.\n"
             << "  -s Manually set the starting number of stones "
             << "in each pile.\n"
             << "  -t Run doctests.\n" 
             << "     > If no arguments are given, the number of test cases "
             << "and assertions\n" 
             << "       that passed/failed will be displayed.\n"
             << "     > If arguments are given, they may change was is "
             << "displayed.\n"
             << "       > --dt-s will display all successful "
             << "assertions.\n"
             << "       > --dt-ltc will list all test cases by name.\n"
             << "       > For a list of all doctest command line argument "
             << "options, visit:\n"
             << "         https://github.com/onqtam/doctest/blob/master"
             << "/doc/markdown/commandline.md\n";

  exit(0);
}

