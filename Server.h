#pragma once

#include "TCPListener.h"
#include "MessageBuffer.h"
#include <map>
#include "GameWorld.hpp"

class TCPListener;
class TCPStream;

class Server
{
public:
	Server(int port=9500);
	~Server();

	int AddConnection(TCPStream* stream);
	int RemoveConnection(TCPStream* stream);

	void Start();
	void Shutdown();

	void PutMessage(const Message& mess);

private:
	GameWorld* world;
	TCPListener* listener;
	std::map<int, TCPStream*> connections;
	MessageBuffer* mBuffer;


};

