#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <type_traits>

#include <doctest.h>
#include "../src/rational.h"

const rational<int> zero = rational<int>{0};
const rational<int> one = rational<int>{1};

SCENARIO( "Check multiplication") {
  GIVEN( "a single rational" ) {
    WHEN("multiplied to itself") {
      THEN( "it should equal a*a" ) {
        REQUIRE (one*one == one);
        REQUIRE (rational<int>{13/3}+rational<int>{13/3} == rational<int>{26/3});
      }
    }
    WHEN("zero is multiplied by anything") {
      THEN( "the result is zero" ) {
        REQUIRE (zero*zero == zero);
        REQUIRE (one*zero == zero);
        REQUIRE (zero*one == zero);
        REQUIRE (rational<int>{2}*zero == zero);
        REQUIRE (zero*rational<int>{-22,7} == zero);
      }
    }
    WHEN("one is multiplied by anything") {
      THEN( "the value is unchanged" ) {
        REQUIRE (zero*one == zero);
        REQUIRE (rational<int>{13}*one == rational<int>{13});
        REQUIRE (rational<int>{-34}*one == rational<int>{-34});
        REQUIRE (rational<int>{1,9}*one == rational<int>{1,9});
        REQUIRE (one*rational<int>{-22,7} == rational<int>{-22,7});
      }
    }
  }
  GIVEN( "two rationals" ) {
    REQUIRE (rational<int>{2} * rational<int>{3} == rational<int>{6});
    REQUIRE (rational<int>{5} * rational<int>{-4} == rational<int>{-20});
    WHEN("using *= ") {
      rational<int> a {1,2};
      rational<int> b {2};
      rational<int> c {1,2};
      rational<int> d {2};
      THEN( "a *= b should change a in the same manner as a = a*b" ) {
        REQUIRE (a*b == c*d);
        a*=b;
        REQUIRE (a == c*d);
      }
      AND_THEN( "a*=b should return a reference" ) {
        REQUIRE (std::is_lvalue_reference<decltype(a*=b)>::value == true);
      }
    }
  }
}



