#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <type_traits>

#include <doctest.h>
#include "../src/list.h"

SCENARIO( "Test mesa::list<T>::erase_after") {

  GIVEN( "a non-empty list" ) {
    mesa::list<int> nums;
    nums.push_front(4);
    nums.push_front(3);
    nums.push_front(2);
    nums.push_front(1);


    WHEN( "erase_after is called on a 4-element list" ) {
      auto head = nums.begin();
      CHECK(nums.size() == 4);
      THEN( " begin should erase the 2nd element" ) {
        auto it = nums.erase_after(head);
        CHECK(nums.size() == 3);
        CHECK(*head == 1);
        CHECK(*it == 3);
        ++it;
        CHECK(*it == 4);
      }
      AND_THEN( " begin+1 should remove the third element" ) {
        auto tmp = nums.begin();
        ++tmp;
        auto it = nums.erase_after(tmp);
        CHECK(nums.size() == 3);
        CHECK(*head == 1);
        CHECK(*it == 4);
      }
    }
  }
}



