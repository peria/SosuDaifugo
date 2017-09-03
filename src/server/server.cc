#include "server.h"

#include <iostream>

Server::Server() {
  acceptor_.setup(1234);

  client_ = acceptor_.accept();

  char buf[1024] {};
  client_.read(buf, 1000);
  std::cout << buf << "\n";
}
