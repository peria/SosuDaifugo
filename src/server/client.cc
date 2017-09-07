#include "client.h"

#include <string>
#include "json.h"

Client::Client(Socket&& socket) : socket_(socket) {}

bool Client::shakeHands() {
  Json message(socket_.receiveMessage());
  // TODO: Validate the message
  name_ = message["name"];
  socket_.sendMessage(Json({"name", name_}).dump());
  return true;
}

std::string Client::receiveMessage() const {
  return socket_.receiveMessage();
}

void Client::sendMessage(const std::string& str) const {
  socket_.sendMessage(str);
}
