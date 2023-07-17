//
// Take-away game solution
// Author: Dave Parillo, ID: 123456789
//
#ifndef CISC187_TAKE_AWAY_GAME_H
#define CISC187_TAKE_AWAY_GAME_H

#include <string>
#include <vector>

#include "options.h"

/**
 * Main game controlling logic is located in game.cpp.
 *
 * Design note:
 * To simply manipulating the mesa::game struct used
 * everywhere in this compilation unit,
 * the mesa::game object is declared in an
 * anonymous namespace in game.cpp
 */

namespace mesa {
    struct game {
        std::string player1;
        std::string player2;
        bool player1_turn = true;
        std::vector<int32_t> stones;
    };
}  // end namespace mesa

/**
 * Make players based on cmd line args set.
 *
 * Prompt for either 1 or 2 player names.
 * If playing against the computer, the name is set.
 */
void make_players(const mesa::option& o);
/**
 * Make heaps (piles) based on cmd line args set.
 *
 * Might be random heaps or set by user.
 */
void make_heaps  (const mesa::option& o);
/**
 * This is the main game controller, 
 * responsible for calling most other game functions.
 */
void play        (const mesa::option& o);
void print_stones();

/**
 * Get a response from the user.
 * 
 * Repeat until non-empty data is entered.
 */
std::string get_entry (const std::string& prompt);
/**
 * Get a response from the user.
 * 
 * Repeat until valid int data is entered.
 */
int32_t    get_value (const std::string& prompt);

/**
 * Prints an appropriate prompt based on the player whose turn it is.
 */
void prompt_player();

/**
 * Display the name of the winning player.
 */
void declare_winner();

/**
 * Ask a human which pile to draw from
 * This function is expected to be called before how_many
 * This function will always return a valid index into game.stones
 */
int32_t choose_heap ();

/**
 * Ask a human how many stones to take from the previously selected pile
 * @param pos index into the piles vector
 */
int32_t how_many (size_t pos);

void remove_from(int32_t pos, int32_t amount);

#endif


