#pragma once
#include <algorithm>
#include <array>
#include <compare>
#include <deque>
#include <iostream>
#include <random>

namespace war {
class Card {
public:
  Card(int face_value) : face_value_(face_value) {}
  auto operator<=>(const Card &other) const = default;

  friend std::ostream &operator<<(std::ostream &os, const Card &card) {
    switch (card.face_value_) {
    case 2:
      os << "Two";
      break;
    case 3:
      os << "Three";
      break;
    case 4:
      os << "Four";
      break;
    case 5:
      os << "Five";
      break;
    case 6:
      os << "Six";
      break;
    case 7:
      os << "Seven";
      break;
    case 8:
      os << "Eight";
      break;
    case 9:
      os << "Nine";
      break;
    case 10:
      os << "Ten";
      break;
    case 11:
      os << "Jack";
      break;
    case 12:
      os << "Queen";
      break;
    case 13:
      os << "King";
      break;
    case 14:
      os << "Ace";
      break;
    }
    return os;
  }

private:
  int face_value_;
};

class Deck {
public:
  size_t size() const { return cards_.size(); }
  auto begin() { return cards_.begin(); }
  auto end() { return cards_.end(); }
  bool empty() const { return cards_.empty(); }

  /**
   * @brief Deal a fresh deck of 52 cards in shuffled order.
   * The face values of the cards range from 2 to 14, with 2 representing a Two
   * and 14 representing an Ace.
   *
   * @return A deck of 52 cards, in randomly shuffled order.
   */
  static Deck deal_new_deck() {
    Deck deck{};
    for (int i = 0; i < 52; ++i) {
      // We place [2,14] onto the deck repeatedly
      deck.place_top(i % 13 + 2);
    }
    std::shuffle(deck.begin(), deck.end(), std::mt19937{});
    return deck;
  }

  // Draw a card from the top of the deck, removing and returning it.
  Card draw() {
    auto card = cards_.front();
    cards_.pop_front();
    return std::move(card);
  }

  void place_top(Card &&card) { cards_.emplace_front(card); }

  void place_bottom(Card &&card) { cards_.emplace_back(card); }

  void place_bottom(Deck &&deck) {
    while (!deck.empty()) {
      cards_.emplace_back(deck.draw());
    }
  }

private:
  std::deque<Card> cards_;
};

class WarGame {
public:
  static auto deal(Deck &&deck) -> Deck {
    Deck player1{}, player2{}, spoils{};
    for (int p = 0; !deck.empty(); p ^= 1) {
      if (p == 0) {
        player1.place_top(deck.draw());
      } else {
        player2.place_top(deck.draw());
      }
    }

    while (PlayRound(player1, player2, spoils)) {
    }

    return player2.empty() ? player1 : player2;
  }

  /**
   * @brief Play a round of War.
   * Each player draws a card and places it face up.
   *
   * While the players' cards are equal, repeat the following:
   *  -> Both players place their current card in the spoils pile.
   *  -> Both players draw a card and place it in the spoils pile.
   *  -> Both players draw a card and place it face up.
   *
   * Once one player's card beats the other's,
   * place both remaining face up cards in the spoils pile,
   * sort the spoils pile in decreasing order, and place it at the bottom
   * of the winning player's deck.
   *
   * @return true if the game is
   */
  static bool PlayRound(Deck &player1, Deck &player2, Deck &spoils) {
    std::cout << "Round begins: " << player1.size() << " vs " << player2.size() << '\n';
    const auto RewardVictor = [&](Deck &victor) -> void {
      std::cout << "\t\tMoving " << spoils.size() << " cards\n";
      sort(spoils.begin(), spoils.end(), std::greater<>());
      victor.place_bottom(std::move(spoils));
      spoils = Deck{};
    };

    Card p1 = player1.draw();
    Card p2 = player2.draw();
    std::cout << p1 << " vs " << p2 << '\n';

    while (p1 == p2) {
      std::cout << '\t' << p1 << " and " << p2 << " tie...\n";
      spoils.place_top(std::move(p1));
      spoils.place_top(std::move(p2));

      if (player1.empty() || player2.empty()) {
        if (player1.empty())
          RewardVictor(player2);
        else
          RewardVictor(player1);
        return true;
      }

      spoils.place_top(player1.draw());
      spoils.place_top(player2.draw());

      if (player1.empty() || player2.empty()) {
        if (player1.empty())
          RewardVictor(player2);
        else
          RewardVictor(player1);
        return true;
      }

      p1 = player1.draw();
      p2 = player2.draw();
      std::cout << '\t' << p1 << " vs " << p2 << '\n';
    }
    Deck &victor = p1 < p2 ? player2 : player1;
    spoils.place_top(std::move(p1));
    spoils.place_top(std::move(p2));
    sort(spoils.begin(), spoils.end(), std::greater<>());
    RewardVictor(victor);
    return !player1.empty() && !player2.empty();
  }
};
} // namespace war