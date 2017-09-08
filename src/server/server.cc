#include "server.h"

#include <algorithm>
#include <memory>
#include <random>

#include "game.h"
#include "glog/logging.h"
#include "json.h"

Server::Server() {
  // TODO: Seed a random-like number to |random_|.
  acceptor_.listen(1234);
}

void Server::run() {
  const int n = 1;
  for (int i = 0; i < n; ++i) {
    clients_.emplace_back(new Client(acceptor_.accept()));
    // TODO: Check if shake-hands succeeds.
    clients_.back()->shakeHands();
    LOG(INFO) << "shakehand with " << i + 1 << "/" << n << " clients";
  }
  shareCommonSettings();

  // TODO: make it possible to game for many times.
  std::shuffle(clients_.begin(), clients_.end(), random_);
  Game game(clients_.size(), random_);
  shareGameSettings(game);

  Json json_plays;
  for (auto& c : clients_) {
    json_plays.push_back(Json::parse("[]"));
  }
  while (!game.end()) {
    const int id = game.playing_id();
    Client* client = clients_[id].get();
    Json json {
      {"plays", json_plays},
      {"field", Json(game.field())},
    };
    client->sendMessage(json.dump());
    // TODO: Receive play from |client|.
    // TODO: Simulate client's play.
    //   - Judge and put cards
    //   - Remove cards from the player
    //   - Check if the player wins
    //      - Reduce |num_in_play_|
    //   - "Increment" |id|. it should figure the player in-play.
  }
}

void Server::shareCommonSettings() const {
  const int n = clients_.size();
  for (int i = 0; i < n; ++i) {
    Json json {
        {"players", clients_.size()},
        {"rule", {}},
    };
    clients_[i]->sendMessage(json.dump());
  }
}

void Server::shareGameSettings(const Game& game) const {
  const int n = clients_.size();
  for (int i = 0; i < n; ++i) {
    Json json {
        {"id", i},
        {"cards", game.player(i).serializeCards()},
    };
    clients_[i]->sendMessage(json.dump());
  }
}

