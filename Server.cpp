#include "Server.h"
#include "TCPListener.h"
#include <map>
#include <iostream>

Server::Server(int port)
{
	std::cout << "Creating new Server on port " << port << ".\n";
	std::cout << "Creating new TCPListener on port " << port << ".\n";
	listener = new TCPListener(this);
	std::cout << "TCPListener creation successful." << '\n';
	world = new GameWorld();
}


Server::~Server()
{
	if (listener) {
		delete listener;
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
	if (status && stream) {
		delete stream;
	}
	return status;
	
}

void Server::Shutdown() {
	delete listener;
	listener = nullptr;
}

void Server::PutMessage(Message* mess) {
	mBuffer.PutMessage(mess);
}