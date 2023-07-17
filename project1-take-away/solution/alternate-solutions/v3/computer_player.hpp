//
// Take-away game solution
// Author: Dave Parillo, ID: 123456789
//
#pragma once

//
// Functions to allow the computer to play take-away.
//
// The game must call evaluate_position(std::vector) first.
// Then the game can call choose_heap(int) and how_many() overloads
// and retrieve the computer evaluated postions much like a human player.
//

#include <cstdint>
#include <vector>

/**
 * Evaluate the entire state of the game using the stones provided.
 * 
 * The result of the evaluation is new values for heap and take.
 */

void evaluate_position(const std::vector<uint32_t>& stones);

/**
 * Evaluate the begining and middle state of a game.
 * 
 */
void evaluate_mid(const std::vector<uint32_t>& stones);

/**
 * Evaluate the special case when we have only 2 piles.
 * The winning strategy is to ensure at the end of your turn, both piles are equal
 */
void evaluate_end(const std::vector<uint32_t>& stones);

/**
 * Function to take stones when we hold a winning position.
 * Take stones from a heap that ensures when removed, the nim sum > 0.
 */
void take_some(const std::vector<uint32_t>& stones, const uint32_t sum);

/**
 * A delaying tactic if a losing position is held.
 * Take 1 stone from the biggest heap,
 * in the hope the other player makes a mistake we can take advantage of.
 */
void take_one(const std::vector<uint32_t>& stones);

/**
 * Respond to the game query "Which heap?" to choose from.
 *
 * If the evaluator was unable to choose, then the largest heap is chosen.
 *
 * @return The heap finally chosen by the computer
 * @note the int parameter is unused.
 *       It serves only to distiguish it from the human
 *       version of choose_heap
 */
uint32_t choose_heap (int);

/**
 * Respond to the game query "How many?" stones to pick.
 *
 * If the evaluator was unable to choose, then 1 stone will be chosen.
 * 
 * @return The number of stones finally chosen by the computer
 */
uint32_t how_many ();

