#include "server.h"

#include <algorithm>
#include <memory>
#include <random>

#include "game.h"
#include "glog/logging.h"
#include "json.h"

Server::Server() {
  acceptor_.listen(1234);
}

void Server::run() {
  const int n = 1;
  for (int i = 0; i < n; ++i) {
    clients_.emplace_back(new Client(acceptor_.accept()));
    clients_.back()->shakeHands();
    LOG(INFO) << "shakehand with " << i + 1 << "/" << n << " clients";
  }

  std::shuffle(clients_.begin(), clients_.end(), random_);
  // TODO: make it possible to game for many times.
  Game game(clients_.size(), random_);
  for (int i = 0; i < n; ++i) {
    Json json {
        {"players", n},
        {"rule", {}},
        {"id", i}
    };
    clients_[i]->sendMessage(json.dump());
  }
  while (!game.end()) {
    const int id = game.playing_id();
    // client->sendGameState(game);
  }
}
