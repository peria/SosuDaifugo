#pragma once

#include <random>
#include <deque>
#include <vector>

#include "card.h"
#include "player.h"

class Game {
 public:
  Game(int num_players, std::mt19937& random);

  Card draw();

  bool end() const { return number_in_play_ < 2; }
  int playing_id() const { return playing_id_; }
  Player& player(int i) { return players_[i]; }
  const Player& player(int i) const { return players_[i]; }
  const std::vector<Card>& field() const { return field_; }
  
 private:
  void initDeck();
  void dealCards();

  int playing_id_ = 0;
  const int number_in_play_;
  std::deque<Card> deck_;
  std::vector<Card> field_;
  std::vector<Player> players_;

  std::mt19937& random_;
};

