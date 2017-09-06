#pragma once

#include <string>

// TODO: Fit the structure into a smaller size. (16 bit?)
struct Card {
  enum class Suit : unsigned {
    None,
    Joker,
    Spade,
    Club,
    Diamond,
    Heart,
  };

  explicit Card(const std::string& str);

  bool isJoker() const { return suit == Suit::Joker; }

  Suit suit;
  int rank;
};


