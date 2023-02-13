#include "war.hpp"
#include <iostream>

int main () {
  war::Card a {3}, b {4};
  if (a < b) {
    std::cout << a << " < " << b << "\n";
  } else {
    std::cout << a << " >= " << b << "\n";
  }

  auto deck = war::Deck::deal_new_deck();
  for (auto& c : deck) {
    std::cout << c << '\n';
  }

  auto winning_hand = war::WarGame::deal(std::move(deck));

  for (auto& c : winning_hand) {
    std::cout << c << '\n';
  }

  return 0;
}