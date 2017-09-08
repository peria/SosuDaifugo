#include "game.h"

#include <random>
#include <vector>

#include "json.h"

Game::Game(int num_players, std::mt19937& random)
  : number_in_play_(num_players),
    players_(num_players),
    random_(random) {
}

