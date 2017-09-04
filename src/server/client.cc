#include "client.h"

#include <string>
#include "json.h"

Client::Client(Socket&& socket) : socket_(socket) {}

bool Client::shakeHands() {
  // Player -> Server
  Json message(socket_.receiveMessage());
  // TODO: Validate the message
  name_ = message["name"];
  // Server -> Player
  socket_.sendMessage(Json({"name", name_}).dump());
  return true;
}

