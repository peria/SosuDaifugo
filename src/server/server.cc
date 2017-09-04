#include "server.h"

#include <iostream>

Server::Server() {
  acceptor_.listen(1234);
}

void Server::run() {
  const int n = 4;
  for (int i = 0; i < n; ++i) {
    clients_.emplace_back(acceptor_.accept());
    clients_.back().shakeHands();
  }

  // // while (true) {
  // Game game;
  // while (!game.end()) {
  //   // turn
  // }
  // // report result
  // // }  // while
}
