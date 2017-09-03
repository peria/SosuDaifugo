#include <iostream>

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, const char* argv[]) {
  int sock0 = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(1234);
  addr.sin_addr.s_addr = INADDR_ANY;
  bind(sock0, (struct sockaddr*)&addr, sizeof(addr));
  
  // wait
  listen(sock0, 5);

  struct sockaddr_in client;
  unsigned int len = sizeof(client);
  int sock = ::accept(sock0, (struct sockaddr*)&client, &len);

  char buf[1024] {};
  recv(sock, buf, 1000, 0);
  std::cout << buf << "\n";

  // close a session
  close(sock);
  // close the listening port
  close(sock0);

  return 0;
}
