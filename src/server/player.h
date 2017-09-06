#pragma once

#include "client.h"

class Player {
 public:
  Player(const Client& client);
  
 private:
  const Client& client_;
};

