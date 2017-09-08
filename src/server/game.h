#pragma once

#include <random>
#include <vector>

#include "card.h"
#include "player.h"

class Game {
 public:
  Game(int num_players, std::mt19937& random);

  bool end() const { return number_in_play_ < 2; }
  int playing_id() const { return playing_id_; }

 private:
  int playing_id_ = 0;
  const int number_in_play_;
  std::vector<Card> deck_;
  std::vector<Player> players_;
  std::mt19937& random_;
};

