#include "client.h"

#include <string>
#include "glog/logging.h"
#include "json.h"

Client::Client(Socket&& socket) : socket_(socket) {}

bool Client::shakeHands() {
  Json message = Json::parse(socket_.receiveMessage());
  name_ = (message.find("name") != message.end()) ? message["name"] : "NoName";
  socket_.sendMessage(Json({{"name", name_}}).dump());
  return true;
}

std::string Client::receiveMessage() const {
  return socket_.receiveMessage();
}

void Client::sendMessage(const std::string& str) const {
  socket_.sendMessage(str);
}
