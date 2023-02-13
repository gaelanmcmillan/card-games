#include "war.hpp"
#include <algorithm>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Adding cards to deck", "[deck]") {
  GIVEN("A deck with no cards") {
    war::Deck deck{};

    WHEN("Adding 3 default constructed cards with values 1, 2, 3") {
      deck.place_top(war::Card(1));
      deck.place_top(war::Card(2));
      deck.place_top(war::Card(3));

      THEN("The deck should have deck.size() == 3") {
        REQUIRE(deck.size() == 3);
      }

      THEN("The cards should come off the top of the deck in reverse order: "
           "3,2,1") {
        REQUIRE(deck.draw() == war::Card(3));
        REQUIRE(deck.draw() == war::Card(2));
        REQUIRE(deck.draw() == war::Card(1));
      }
    }

    WHEN("Adding several cards in unsorted order and sorting") {
      for (auto num : {14, 12, 6, 2, 1, 8, 9, 10}) {
        deck.place_top(war::Card(num));
      }

      sort(deck.begin(), deck.end());

      THEN("The cards should be in sorted order") {
        REQUIRE(std::is_sorted(deck.begin(), deck.end()));
      }
    }
  }
}

TEST_CASE("Placing a deck on the bottom of another deck", "[deck]") {
  GIVEN("Two decks, one with cards 1, 2, 3 and one with cards 4,5,6") {
    war::Deck deck1;
    deck1.place_bottom(war::Card(1));
    deck1.place_bottom(war::Card(2));
    deck1.place_bottom(war::Card(3));

    war::Deck deck2;
    deck2.place_top(war::Card(6));
    deck2.place_top(war::Card(5));
    deck2.place_top(war::Card(4));

    WHEN("deck1 places deck2 on the bottom") {
      deck1.place_bottom(std::move(deck2));

      THEN("deck1 has size 6 and deck2 has size 0") {
        REQUIRE(deck1.size() == 6);
        REQUIRE(deck2.size() == 0);

        AND_THEN("deck1 has cards 1, 2, 3, 4, 5, 6 in order") {
          auto iter = deck1.begin();
          for (int expected = 1; expected <= 6; ++expected) {
            REQUIRE(*iter == war::Card(expected));
            ++iter;
          }
        }
      }
    }
  }
}