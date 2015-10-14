#include "Server.h"
#include "TCPListener.h"
#include <map>
#include <iostream>

Server::Server(int port) 
	: listener(new TCPListener(this))
	, world(new GameWorld())
	, mBuffer(new MessageBuffer())
{
	std::cout << "Creating new Server on port " << port << ".\n";
	
	std::cout << "TCPListener creation successful." << '\n';
}


Server::~Server()
{
	if (listener) {
		delete listener;
	}
	if (mBuffer) {
		delete mBuffer;
	}
}

void Server::Start() {
	listener->Listen();
}

int Server::AddConnection(TCPStream* stream) {
	connections.insert(std::pair<int, TCPStream*>(stream->GetSocket(), stream));
	std::cout << "Added socket " << stream->GetSocket() << " to the connection list." << '\n';
	return 0;
}

int Server::RemoveConnection(TCPStream* stream) {
	int status = connections.erase(stream->GetSocket());
	if (status) {
		delete stream;
	}
	return status;
	
}

void Server::Shutdown() {
	for (int i = 0; i < connections.size(); ++i) {
		RemoveConnection(connections.begin()->second);
	}
	delete listener;
	listener = nullptr;
}

void Server::PutMessage(const Message& mess) {
	mBuffer->PutMessage(mess);
}