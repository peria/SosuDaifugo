#pragma once

#include <memory>
#include <random>
#include <vector>

#include "card.h"
#include "client.h"
#include "player.h"

class Game {
 public:
  Game(const std::vector<Client>&);

  bool end() const { return false; }

 private:
  std::vector<Card> deck_;
  std::vector<std::unique_ptr<Player>> players_;
  std::mt19937 random_;
};

