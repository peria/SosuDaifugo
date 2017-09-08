#include "player.h"

#include <vector>

#include "card.h"
#include "json.h"

Player::Player() {}

void Player::deal(const Card& card) {
  cards_.push_back(card);
}

Json Player::serializeCards() const {
  return Json(cards_);
}
