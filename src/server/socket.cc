#include "socket.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

Socket::Socket() : descriptor_(kInvalid) {}

Socket::Socket(int descriptor) : descriptor_(descriptor) {}

Socket::~Socket() {
  if (!isValid())
    close(descriptor_);
}

void Socket::setup(int port) {
  if (isValid())
    return;
  
  descriptor_ = socket(AF_INET, SOCK_STREAM, 0);

  // set up acceptor
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY;
  bind(descriptor_, (struct sockaddr*)&addr, sizeof(addr));

  // wait
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

void Socket::read(void* buf, size_t size) const {
  if (!isValid())
    return;

  // TODO: recv() may fail to receive all message in one call.
  recv(descriptor_, buf, size, 0);
}
