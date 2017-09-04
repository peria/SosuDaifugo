CXX = clang++
INCLUDE = -I..
CXXFLAGS = -O2 -std=c++11 -W $(INCLUDE)


SRC = main.cc server.cc socket.cc client.cc
OBJ = $(SRC:.cc=.o)

all: server

server: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cc %.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	$(RM) -rf $(OBJ) server
