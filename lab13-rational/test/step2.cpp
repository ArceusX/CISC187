#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cstdint>
#include <doctest.h>
#include "../src/rational.h"

SCENARIO( "Test rational construction") {
  GIVEN( "a default rational" ) {
    rational<int> r;
    THEN( "the default value should be 0" ) {
      REQUIRE (r.numerator() == 0);
      REQUIRE (r.denominator() == 1);
    }
  }
  GIVEN( "a rational constructed with a int32_t" ) {
      rational<std::int32_t> r;
      THEN( "the value should be 0" ) {
        REQUIRE (r.numerator() == 0);
        REQUIRE (r.denominator() == 1);
      }
    }
    GIVEN( "a rational constructed with a size_t" ) {
      rational<std::size_t> r;
      THEN( "the value should be 0" ) {
        REQUIRE (r.numerator() == 0);
        REQUIRE (r.denominator() == 1);
      }
    }

    GIVEN( "a rational constructed with a long" ) {
      rational<long> r;
      THEN( "the value should be 0" ) {
        REQUIRE (r.numerator() == 0);
        REQUIRE (r.denominator() == 1);
      }
    }

}



