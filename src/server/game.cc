#include "game.h"

#include <random>
#include <vector>

#include "glog/logging.h"
#include "json.h"

Game::Game(int num_players, std::mt19937& random)
  : number_in_play_(num_players),
    players_(num_players),
    random_(random) {
  initDeck();
  dealCards();
}

Card Game::draw() {
  if (deck_.empty())
    return Card();

  Card card = deck_.front();
  deck_.pop_front();
  return card;
}

void Game::initDeck() {
  CHECK(deck_.empty());

  // Two Jokers
  std::string card("JO");
  deck_.push_back(card);
  deck_.push_back(card);
  // Number cards
  for (char suit : std::string("SCDH")) {
    card[0] = suit;
    for (char rank : std::string("A23456789TJQK")) {
      card[1] = rank;
      deck_.push_back(card);
    }
  }

  std::shuffle(deck_.begin(), deck_.end(), random_);
}

void Game::dealCards() {
  int n = std::min<int>(11, deck_.size() / players_.size());
  for (Player& player : players_) {
    for (int i = 0; i < n; ++i) {
      player.deal(draw());
    }
  }
}
