#pragma once

#include "TCPListener.h"
#include "MessageBuffer.h"
#include <map>

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

	void PutMessage(Message* mess);

private:
	TCPListener* listener;
	std::map<int, TCPStream*> connections;
	MessageBuffer mBuffer;


};

