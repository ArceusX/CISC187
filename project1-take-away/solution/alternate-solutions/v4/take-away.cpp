#define DOCTEST_CONFIG_NO_UNPREFIXED_OPTIONS
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest.h>

#include "help.h"
#include "game.h" 
#include "utility.h"

#include <unistd.h>
#include <iostream>
#include <string>

using std::string;

int main(int argc, char* argv[]) {   
   // Seed the random number once at start of program.
   srand(time(NULL));

   // Prepare doctest.
   doctest::Context context;
   int doctest_results;

   // Set default settings.
   bool defaultGame = true; //multiplayer game
   int piles = 0, stones = 0; //indicate random number of piles and stones

   // Loop through command line arguments.
   int c;
   while ((c = getopt (argc, argv, "hcp:s:t")) != -1) {
      string errorMessage = "   Invalid input for number of ";

      switch (c) {
         case 'h': //display help text and exit
            displayHelp();

         case 'c': //play against the computer
            defaultGame = false;
            break;

         case 'p': //set the number of piles
            errorMessage += "piles.";
            if (stringToInt(argv[optind-1], &piles, errorMessage))
               if (checkIntRange(piles, MAX_PILES, errorMessage))
                  break;
            exit(-1); //exit if not given a valid input

         case 's': //set the number of stones in each pile
            errorMessage += "stones in each pile.";
            if (stringToInt(argv[optind-1], &stones, errorMessage))
               if (checkIntRange(stones, MAX_STONES, errorMessage))
                  break;
            exit(-1); //exit if not given a valid input
         
         case 't': //run unit tests and exit
            context.applyCommandLine(argc, argv);
            context.setOption("no-breaks", true); //continue if assertions fail
            doctest_results = context.run();
            if(context.shouldExit()) //honor query flags and --exit 
               return doctest_results;
            exit(0);

      }
   }
   
   // If reached this point, play take-away.
   playTakeAway(defaultGame, piles, stones);
}

