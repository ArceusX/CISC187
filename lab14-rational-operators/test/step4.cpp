#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <type_traits>

#include <doctest.h>
#include "../src/rational.h"

const rational<int> zero = rational<int>{0};
const rational<int> one = rational<int>{1};

SCENARIO( "Check subtraction") {
  GIVEN( "a single rational" ) {
    WHEN("subtracted from itself") {
      THEN( "result should equal 0" ) {
        REQUIRE (one-one == zero);
        REQUIRE (rational<int>{13/3}-rational<int>{13/3} == zero);
      }
    }
    WHEN("zero is subtracted from anything") {
      THEN( "the identity value should be preserved" ) {
        REQUIRE (zero-zero == zero);
        REQUIRE (one-zero == one);
        REQUIRE (rational<int>{2}-zero == rational<int>{2});
        REQUIRE (rational<int>{-22,7}-zero == rational<int>{-22,7});
      }
    }
    WHEN("one is subtracted from anything") {
      THEN( "the value should decrease by 1" ) {
        REQUIRE (rational<int>{2}-one == one);
        REQUIRE (rational<int>{-22,7}-one == rational<int>{-29,7});
        REQUIRE (rational<int>{1,2}-one == rational<int>{-1,2});
      }
    }
  }
  GIVEN( "two rationals" ) {
    REQUIRE (rational<int>{2} - rational<int>{3} == rational<int>{-1});
    REQUIRE (rational<int>{2} - rational<int>{-2} == rational<int>{4});
    REQUIRE (rational<int>{22,7} - rational<int>{-22,7} == rational<int>{44,7});
    WHEN("using -= ") {
      rational<int> a {1,2};
      rational<int> b {2};
      rational<int> c {1,2};
      rational<int> d {2};
      THEN( "a -= b should change a in the same manner as a = a-b" ) {
        REQUIRE (a-b == c-d);
        a-=b;
        REQUIRE (a == c-d);
      }
      AND_THEN( "a-=b should return a reference" ) {
        REQUIRE (std::is_lvalue_reference<decltype(a-=b)>::value == true);
      }
    }
  }
}



