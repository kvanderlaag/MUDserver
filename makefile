CC=g++
CFLAGS=-c -std='c++14' -fext-numeric-literals
LDFLAGS=-lstdc++ -lpthread -levent_core
SOURCES=Battle.cpp BattleList.cpp ConnectionList.cpp EntityList.cpp FileParser.cpp GameEntity.cpp GameWorld.cpp Item.cpp Message.cpp MessageBuffer.cpp MUDServer_libevent.cpp NPC.cpp Parser.cpp Player.cpp PlayerStats.cpp Room.cpp Server.cpp TCPListener.cpp TCPStream.cpp Utility.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=MUDserver

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
