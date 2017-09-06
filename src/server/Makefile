INCLUDE = -I..
LIBRARY = -lglog -lgflags

CXX = clang++
CXXFLAGS = -O2 -std=c++11 -W $(INCLUDE)


SRC = main.cc
SRC += socket.cc server.cc client.cc  # libraries
SRC += card.cc player.cc game.cc      # game
OBJ = $(SRC:.cc=.o)

all: server

server: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBRARY)

%.o: %.cc %.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	$(RM) -rf $(OBJ) server
