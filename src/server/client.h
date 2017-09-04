#pragma once

#include <string>
#include "socket.h"

class Client {
 public:
  Client(Socket&& socket);

  bool shakeHands();

 private:
  const Socket socket_;
  std::string name_;
};
