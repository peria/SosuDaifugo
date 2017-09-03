#pragma once

#include "socket.h"

class Server {
 public:
  Server();

 private:
  Socket acceptor_;
  Socket client_;
};
