#pragma once

#include <sys/types.h>

class Socket {
 public:
  using Descriptor = int;
  static const Descriptor kInvalid = -1;

  Socket();
  ~Socket();

  void setup(int port);
  Socket accept() const;
  void read(void* buf, size_t size) const;

  bool isValid() const { return descriptor_ != kInvalid; }

 private:
  explicit Socket(int);

  Descriptor descriptor_ = kInvalid;
};
