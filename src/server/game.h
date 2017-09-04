#pragma once

#include <vector>

class Game {
 public:
  Game();

  bool end() const { return false; }

 private:
  std::vector<Card> deck_;
};

