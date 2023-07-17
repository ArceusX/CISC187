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

void evaluate_position(const std::vector<uint32_t>& stones) {
  heap = UINT32_MAX;
  take = 0u;
  switch (stones.size()) {
    case 1: 
      heap = 0u;
      take = stones[0];
      break;
    case 2: 
      evaluate_mid(stones);
      break;
    default: 
      evaluate_mid(stones);
      break;
  }

}

void evaluate_mid(const std::vector<uint32_t>& stones) {
  uint32_t sum = 0;
  for (const auto& i : stones) {
    sum = sum ^ i;                 // compute binary sum of heaps
  }

  if (sum > 0) {                     // currently a winning position
    take_some(stones, sum);
  } else {                            // currently a losing position
    take_one(stones);
  }
}

void take_some(const std::vector<uint32_t>& stones, const uint32_t sum) {
    uint32_t index = 0;
    for (const auto& i : stones) {
      uint32_t tmp = sum ^ i;
      if (tmp < i) {
        take = i - tmp;
        heap = index;
        break;
      }
      ++index;
    }
}

void take_one(const std::vector<uint32_t>& stones) {
  auto tmp = 0u;
  for (auto i = 0u; i < stones.size()-1; ++i) {  // pick biggest heap
    tmp = stones[i] >= stones[i+1]? i: i+1;
  }
  heap = tmp;
  take = 1u;                      // take the minimum amount allowed
}

uint32_t choose_heap (int) {
  return heap;
}

uint32_t how_many () {
  return take;
}

