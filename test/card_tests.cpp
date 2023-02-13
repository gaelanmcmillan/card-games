#include "war.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Card comparison", "[card]") {
  GIVEN("Two cards, one Six and one Twelve") {
    war::Card a6(6);
    war::Card a12(12);

    WHEN("Comparing the two cards") {
      THEN("The Six should evaluate less than the Twelve") {
        REQUIRE(a6 < a12);
        REQUIRE(a12 > a6);
      }
    }
  }

  GIVEN("Three cards, two Sixes and a Two") {
    war::Card a6(6);
    war::Card another6(6);
    war::Card a2(2);

    WHEN("Comparing the Sixes") {
      THEN("The Sixes should evaluate equal") {
        REQUIRE(a6 == another6);
      }
    }
  }
}