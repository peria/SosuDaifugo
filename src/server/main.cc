#include "gflags/gflags.h"
#include "glog/logging.h"
#include "server.h"

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, true);

  Server server;
  server.run();
  
  return 0;
}
