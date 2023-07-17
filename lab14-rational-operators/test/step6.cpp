#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <type_traits>

#include <doctest.h>
#include "../src/rational.h"

static const rational<int> zero = rational<int>{0};
static const rational<int> one = rational<int>{1};
static const auto inf = rational<int>{0,0};

SCENARIO( "Check division") {
  GIVEN( "a single rational" ) {
    WHEN("divided into itself") {
      THEN( "result should equal 1" ) {
        REQUIRE (one/one == one);
        REQUIRE (rational<int>{3}/rational<int>{3} == one);
        REQUIRE (rational<int>{13/3}/rational<int>{13/3} == one);
      }
    }
    WHEN("one is divided into anything") {
      THEN( "the value should remain unchanged" ) {
        REQUIRE (rational<int>{2}/one == rational<int>{2});
        REQUIRE (rational<int>{-22,7}/one == rational<int>{-22,7});
        REQUIRE (rational<int>{1,2}/one == rational<int>{1,2});
      }
    }
    WHEN("zero is divided into anything") {
      THEN( "the result should be infinity" ) {
        REQUIRE (zero/zero == inf);
        REQUIRE (one/zero == inf);
        REQUIRE (rational<int>{2}/zero == inf);
        REQUIRE (rational<int>{-22,7}/zero == inf);
      }
    }
  }
  GIVEN( "two rationals" ) {
    REQUIRE (rational<int>{2} / rational<int>{3} == rational<int>{2,3});
    REQUIRE (rational<int>{2} / rational<int>{-2} == rational<int>{-1});
    REQUIRE (rational<int>{22,7} / rational<int>{-22,7} == rational<int>{-1});
    WHEN("using /= ") {
      rational<int> a {1,2};
      rational<int> b {2};
      rational<int> c {1,2};
      rational<int> d {2};
      THEN( "a /= b should change a in the same manner as a = a/b" ) {
        REQUIRE (a/b == c/d);
        a/=b;
        REQUIRE (a == c/d);
      }
      AND_THEN( "a/=b should return a reference" ) {
        REQUIRE (std::is_lvalue_reference<decltype(a/=b)>::value == true);
      }
    }
  }
}



