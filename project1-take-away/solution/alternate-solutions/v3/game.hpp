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
        bool is_random = true;
        uint32_t piles = 0;
        uint32_t stones = 0;
    };
    struct game {
        std::string player1;
        std::string player2;
        bool player1_turn = true;
        std::vector<uint32_t> stones;
    };
}
void init_players(mesa::option cmd_line_options);
void init_heaps(mesa::option cmd_line_options);
void play(mesa::option cmd_line_options);

void print_state();

std::string get_entry (const std::string& prompt);

uint32_t get_val (const std::string& prompt);

/**
 * Prints an appropriate prompt based on the player whose turn it is.
 */
void prompt_player();

/**
 * Display the name of the winning player.
 */
void declare_winner();


uint32_t choose_heap ();

uint32_t how_many (size_t pos);

void remove_from(const uint32_t pos, const uint32_t amount);

