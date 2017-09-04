#pragma once

#include <vector>

#include "client.h"
#include "socket.h"

class Server {
 public:
  Server();

  void run();

 private:
  Socket acceptor_;
  std::vector<Client> clients_;
};
