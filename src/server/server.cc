#include "server.h"

#include <iostream>

#include "game.h"
#include "glog/logging.h"

Server::Server() {
  acceptor_.listen(1234);
}

void Server::run() {
  // TODO: Make the number of players flexible.
  const int n = 4;
  for (int i = 0; i < n; ++i) {
    clients_.emplace_back(acceptor_.accept());
    clients_.back().shakeHands();
  }

  // TODO: make it possible to game for many times.
  Game game(clients_);
  // while (!game.end()) {
  //   // turn
  // }
  // // report result

  // not reached
  CHECK(false);
}
