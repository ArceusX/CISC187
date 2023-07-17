//
// Take-away game solution
// Author: Dave Parillo, ID: 123456789
//
#ifndef CISC187_TAKE_AWAY_COMPUTER_PLAYER_H
#define CISC187_TAKE_AWAY_COMPUTER_PLAYER_H

//
// Functions to allow the computer to play take-away.
//
// The game must call evaluate(std::vector) first.
// Then the game can call choose_heap(int) and how_many() overloads
// and retrieve the computer evaluated postions much like a human player.
//

#include <cstdint>
#include <vector>

/**
 * Evaluate the game and determine what move to make.
 * Calls take_some or take_one.
 */
void evaluate(const std::vector<int32_t>& piles);

/**
 * Function to take stones when we hold a winning position.
 * Take stones from a heap that ensures when removed, the nim sum > 0.
 */
void take_some(const std::vector<int32_t>& piles, int32_t sum);

/**
 * A delaying tactic if a losing position is held.
 * Take 1 stone from the biggest heap,
 * in the hope the other player makes a mistake we can take advantage of later.
 */
void take_one(const std::vector<int32_t>& piles);

/**
 * Respond to the game query "Which heap?" to choose from.
 *
 * If the evaluator was unable to choose, then the largest heap is chosen.
 *
 * @return The heap finally chosen by the computer
 * @note the int parameter is unused.
 *       It serves only to distiguish it from the human
 *       overload of choose_heap
 */
int32_t choose_heap (int /*unused*/);

/**
 * Respond to the game query "How many?" stones to pick.
 *
 * If the evaluator was unable to choose, then 1 stone will be chosen.
 * 
 * @return The number of stones finally chosen by the computer
 */
int32_t how_many ();

#endif

