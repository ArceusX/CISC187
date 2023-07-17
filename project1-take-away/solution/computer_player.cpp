//
// Take-away game solution
// Author: Dave Parillo, ID: 123456789
//
#include "computer_player.h"

#include <algorithm>
#include <cstdint> 
#include <vector>

namespace {
  int32_t heap = INT32_MAX;
  int32_t take = 0;
} // end anonymous namespace

void evaluate(const std::vector<int32_t>& piles) {
  int32_t sum = 0;
  for (const auto& stones : piles) {
    sum = sum ^ stones;     // compute nim sum of heaps
  }
  take_some(piles, sum);
}

void take_some(const std::vector<int32_t>& piles, const int32_t sum) {
  if (sum == 0) {       // currently a losing position
    take_one (piles);
    return;
  }
  // currently a winning position
  int32_t best_pile = 0;           // technically, just the first pile that allows taking the sum to 0
  for (const auto& stones : piles) {
    int32_t surplus = sum ^ stones;
    if (surplus < stones) {          // found a pile that will reduce the sum to zero
      take = stones - surplus;
      heap = best_pile;
      break;
    }
    ++best_pile;
  }
}

void take_one(const std::vector<int32_t>& piles) {
  auto it = std::max_element(piles.begin(), piles.end());
  heap = std::distance(piles.begin(), it);
  take = 1;                      // take the minimum amount allowed
}

int32_t choose_heap (int /*unused*/) {
  return heap;
}

int32_t how_many () {
  return take;
}

