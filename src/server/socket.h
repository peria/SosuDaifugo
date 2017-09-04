#pragma once

#include <sys/types.h>
#include <string>

class Socket {
 public:
  using Descriptor = int;
  static const Descriptor kInvalid = -1;

  Socket();
  ~Socket();

  // |port| での待ち状態を作る
  void listen(int port);
  // listen() での待ち状態から接続を pop する
  Socket accept() const;

  std::string receiveMessage() const;
  void sendMessage(const std::string& str) const;

  bool isValid() const { return descriptor_ != kInvalid; }

 private:
  explicit Socket(int);
  ssize_t read(void* buf, size_t size) const;

  Descriptor descriptor_ = kInvalid;
};
