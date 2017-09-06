#include "game.h"

#include <algorithm>
#include <random>
#include <vector>

#include "client.h"

using std::vector;

Game::Game(const vector<Client>& clients) {
  for (const auto& client : clients) {
    players_.emplace_back(new Player(client));
  }
  std::shuffle(players_.begin(), players_.end(), random_);
}

