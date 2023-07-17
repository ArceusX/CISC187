//
// Take-away game solution
// Author: Dave Parillo, ID: 123456789
//
#include "computer_player.hpp"

#include <cstdint> 
#include <algorithm>
#include <vector>

static uint32_t heap = UINT32_MAX;
static uint32_t take = 0;

void evaluate(const std::vector<uint32_t>& piles) {
  uint32_t sum = 0;
  for (const auto& stones : piles) {
    sum = sum ^ stones;                 // compute nim sum of heaps
  }

  if (sum > 0) {                        // currently a winning position
    take_some(piles, sum);
  } else {                              // currently a losing position
    take_one(piles);
  }
}

void take_some(const std::vector<uint32_t>& piles, const uint32_t sum) {
    uint32_t best_pile = 0;           // technically, just the first pile that allows taking the sum to 0
    for (const auto& stones : piles) {
      uint32_t surplus = sum ^ stones;
      if (surplus < stones) {          // found a pile that will reduce the sum to zero
        take = stones - surplus;
        heap = best_pile;
        break;
      }
      ++best_pile;
    }
}

void take_one(const std::vector<uint32_t>& piles) {
  const auto it = std::max_element(piles.begin(), piles.end());
  heap = std::distance(piles.begin(), it);
  take = 1u;
}

uint32_t choose_heap (int) {
  return heap;
}

uint32_t how_many () {
  return take;
}
