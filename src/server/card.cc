#include "card.h"

#include <cstdlib>
#include <cstring>
#include <string>

#include "glog/logging.h"

namespace {

Card::Suit toSuit(const std::string& str) {
  if (str == "JO") {
    return Card::Suit::Joker;
  }

  switch (str[0]) {
  case 'S':
    return Card::Suit::Spade;
  case 'C':
    return Card::Suit::Club;
  case 'D':
    return Card::Suit::Diamond;
  case 'H':
    return Card::Suit::Heart;
  }

  return Card::Suit::None;
}

int toRank(const std::string& str) {
  // Jocker does not have a specific rank.
  if (str == "JO") {
    return -1;
  }

  const char* p = str.data();
  if (std::strchr("SCDH", *p)) {
    ++p;
  }

  DCHECK(p);

  // Work for special characters of ranks. A/J/Q/K
  switch (*p) {
  case 'A':
    return 1;
  case 'J':
    return 11;
  case 'Q':
    return 12;
  case 'K':
    return 13;
  }

  DCHECK(std::isdigit(*p));
  return std::atoi(p);
}

}

Card::Card(const std::string& str)
  : suit(toSuit(str)),
    rank(toRank(str)) {}
