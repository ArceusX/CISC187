#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <type_traits>

#include <doctest.h>
#include "../src/rational.h"

const rational<int> zero = rational<int>{0};
const rational<int> one = rational<int>{1};

SCENARIO( "Check addition") {
  GIVEN( "a single rational" ) {
    WHEN("added to itself") {
      THEN( "it should equal a+a" ) {
        REQUIRE (one+one == rational<int>{2});
        REQUIRE (rational<int>{13/3}+rational<int>{13/3} == rational<int>{26/3});
      }
    }
    WHEN("zero is added to anything") {
      THEN( "the identity value should be preserved" ) {
        REQUIRE (zero+zero == zero);
        REQUIRE (one+zero == one);
        REQUIRE (zero+one == one);
        REQUIRE (rational<int>{2}+zero == rational<int>{2});
        REQUIRE (zero+rational<int>{-22,7} == rational<int>{-22,7});
      }
    }
    WHEN("one is added to anything") {
      THEN( "the value should increase by 1" ) {
        REQUIRE (rational<int>{2}+one == rational<int>{3});
        REQUIRE (one+rational<int>{-22,7} == rational<int>{-15,7});
      }
    }
  }
  GIVEN( "two rationals" ) {
    REQUIRE (rational<int>{2} + rational<int>{3} == rational<int>{5});
    REQUIRE (rational<int>{2} + rational<int>{-2} == zero);
    WHEN("using += ") {
      rational<int> a {1,2};
      rational<int> b {2};
      rational<int> c {1,2};
      rational<int> d {2};
      THEN( "a += b should change a in the same manner as a = a+b" ) {
        REQUIRE (a+b == c+d);
        a+=b;
        REQUIRE (a == c+d);
      }
      AND_THEN( "a+=b should return a reference" ) {
        REQUIRE (std::is_lvalue_reference<decltype(a+=b)>::value == true);
      }
    }
  }
}



