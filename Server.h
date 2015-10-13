#pragma once

#include "TCPListener.h"
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

private:
	TCPListener* listener;
	std::map<int, TCPStream*> connections;


};

