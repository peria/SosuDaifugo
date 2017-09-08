#pragma once

#include <memory>
#include <random>
#include <vector>

#include "client.h"
#include "socket.h"

class Server {
 public:
  Server();

  void run();

 private:
  Socket acceptor_;
  std::vector<std::unique_ptr<Client>> clients_;
  std::mt19937 random_;
};
