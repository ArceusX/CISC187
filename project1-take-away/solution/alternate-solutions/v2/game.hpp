//
// Take-away game solution
// Author: Dave Parillo, ID: 123456789
//
#pragma once

#include <string>
#include <vector>

namespace mesa {
    struct option {
        bool has_ai = false;
        uint32_t piles = 0;
        uint32_t stones = 0;
    };
    struct game {
        std::string player1;
        std::string player2;
        bool player1_turn = true;
        std::vector<uint32_t> stones;
    };
}  // end namespace mesa

void make_players(const mesa::option& cmd_line_options);
void make_heaps  (const mesa::option& cmd_line_options);
/**
 * This is the main game controller, 
 * responsible to calling most other game functions.
 */
void play        (const mesa::option& cmd_line_options);
void print_stones();

std::string get_entry (const std::string& prompt);
uint32_t    get_value (const std::string& prompt);

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
 * This function will alway return a valid index into game.stones
 */
uint32_t choose_heap ();

/**
 * Ask a human how many stones to take from the previously selected pile
 */
uint32_t how_many (size_t pos);

void remove_from(const uint32_t pos, const uint32_t amount);

