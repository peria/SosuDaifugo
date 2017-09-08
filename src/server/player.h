#pragma once

#include <vector>

#include "card.h"
#include "json.h"

class Player {
 public:
  Player();

  void deal(const Card& card);
  Json serializeCards() const;

 private:
  std::vector<Card> cards_;
};

