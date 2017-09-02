#pragma once

#include <sys/types.h>

namespace net {

class Socket {
 public:
  using Descriptor = int;
  static const Descriptor kInvalid = -1;

  Socket(Socket &&socket) noexcept;
  ~Socket();

  Socket &operator=(Socket &&socket) noexcept;

  bool isValid() const { return descriptor_ != kInvalid; }

  // Returns the implementation defined socket descriptor.
  Descriptor get() const { return descriptor_; }

  // Reads to |buf|.
  ssize_t read(void* buf, size_t size);
  // Reads exactly |size| byte to |buf|. If error happens or
  // EOF comes before really reading |size| byte, false is returned.
  bool readExactly(void* buf, size_t size);

  ssize_t write(const void* buf, size_t size);
  bool writeExactly(const void* buf, size_t size);
  void flush();

  bool setNodelay();

  bool bindFromAny(int port);
  bool listen(int backlog = 5);

  Socket accept();

 protected:
  explicit Socket(Descriptor sd) : descriptor_(sd) {}

  Descriptor descriptor_;
};

} // namespace net
