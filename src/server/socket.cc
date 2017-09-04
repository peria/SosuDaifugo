#include "socket.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <string>
#include <iostream>

using std::string;

namespace {
constexpr ssize_t kErrorSize = -1;
}  // namespace

Socket::Socket() : descriptor_(kInvalid) {}

Socket::Socket(int descriptor) : descriptor_(descriptor) {}

Socket::~Socket() {
  if (!isValid())
    close(descriptor_);
}

void Socket::listen(int port) {
  if (isValid())
    return;
  
  descriptor_ = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY;
  bind(descriptor_, (struct sockaddr*)&addr, sizeof(addr));

  // TODO: set approprivate size of queue.
  ::listen(descriptor_, 5);
}

Socket Socket::accept() const {
  if (!isValid())
    return Socket();

  struct sockaddr_in client;
  unsigned int len = sizeof(client);
  Socket sock(::accept(descriptor_, (struct sockaddr*)&client, &len));
  return sock;
}

string Socket::receiveMessage() const {
  static char buffer[1024] {};
  static constexpr int kBufferSize = 1000;

  string message;
  while (true) {
    ssize_t size = this->read(buffer, kBufferSize);
    if (size < 0) {
      std::cerr << "Fail to load a message from socket " << descriptor_ << "\n";
      return "";
    }

    buffer[size] = '\0';
    message += buffer;
    if (size < kBufferSize)
      break;
  }
  return message;
}

void Socket::sendMessage(const std::string& str) const {
  // Assume |str| can be sent in one message.
  ::write(descriptor_, str.data(), str.size());
}

ssize_t Socket::read(void* buf, size_t size) const {
  if (!isValid())
    return kErrorSize;

  return recv(descriptor_, buf, size, 0);
}
