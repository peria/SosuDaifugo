#include "socket.h"

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

namespace net {

Socket::Socket(Socket &&socket) noexcept : descriptor_(socket.descriptor_) {
  socket.descriptor_ = kInvalid;
}

Socket::~Socket() {
  if (!isValid())
    return;

  if (::close(descriptor_) < 0) {
    std::cerr << "failed to close socket\n";
  }
}

Socket &Socket::operator=(Socket &&socket) noexcept {
  std::swap(descriptor_, socket.descriptor_);
  return *this;
}

ssize_t Socket::read(void* buf, size_t size) {
  return ::recv(descriptor_, buf, size, 0);
}

bool Socket::readExactly(void* buf, size_t size) {
  while (size > 0) {
    ssize_t s = read(buf, size);
    if (s <= 0) {
      if (s == 0) {
        std::cerr << "unexpected EOF\n";
        return false;
      }
      if (errno == EAGAIN)
        continue;

      std::cerr << "failed to read\n";
      return false;
    }

    size -= s;
    buf = reinterpret_cast<char *>(buf) + s;
  }

  return true;
}

ssize_t Socket::write(const void* buf, size_t size) {
  return ::send(descriptor_, buf, size, 0);
}

bool Socket::writeExactly(const void* buf, size_t size) {
  while (size > 0) {
    ssize_t s = write(buf, size);
    if (s <= 0) {
      if (s == 0) {
        std::cerr << "connection closed\n";
        return false;
      }
      if (errno == EAGAIN)
        continue;

      std::cerr << "faied to write";
      return false;
    }

    size -= s;
    buf = reinterpret_cast<const char *>(buf) + s;
  }

  return true;
}

bool Socket::setNodelay() {
  int flag = 1;
  if (setsockopt(descriptor_, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(flag)) < 0) {
    std::cerr << "failed to set TCP_NODELAY\n";
    return false;
  }

  return true;
}

bool Socket::bindFromAny(int port) {
  struct sockaddr_in reader_addr;
  ::memset(&reader_addr, 0, sizeof(reader_addr));

  reader_addr.sin_family = PF_INET;
  reader_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  reader_addr.sin_port = htons(port);

  if (::bind(descriptor_, reinterpret_cast<struct sockaddr *>(&reader_addr),
             sizeof(reader_addr)) < 0) {
    std::cerr << "bind socket=" << descriptor_ << " port=" << port << "\n";
    return false;
  }

  return true;
}

bool Socket::listen(int backlog) {
  if (::listen(descriptor_, backlog) < 0) {
    std::cerr << "listen socket=" << descriptor_ << " backlog=" << backlog << "\n";
    return false;
  }
  return true;
}

Socket Socket::accept() {
  struct sockaddr_in addr;
  socklen_t len = sizeof(addr);
  int new_fd = ::accept(descriptor_, reinterpret_cast<struct sockaddr *>(&addr), &len);
  if (new_fd < 0) {
    std::cerr << "accept socket=" << descriptor_ << "\n";
    return Socket(kInvalid);
  }

  return Socket(new_fd);
}

} // namespace net
