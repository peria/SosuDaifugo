#pragma once

#include <string>
#include "socket.h"

class Client {
 public:
  Client(Socket&& socket);

  bool shakeHands();
  std::string receiveMessage() const;
  void sendMessage(const std::string& str) const;

  const std::string& name() const { return name_; }

 private:
  const Socket socket_;
  std::string name_;
};
