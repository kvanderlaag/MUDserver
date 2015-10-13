#include "Server.h"
#include "TCPListener.h"
#include <map>
#include <iostream>

using namespace std;


Server::Server(int port)
{
	cout << "Creating new Server on port " << port << ".\n";
	cout << "Creating new TCPListener on port " << port << ".\n";
	listener = new TCPListener(this);
	cout << "TCPListener creation successful." << '\n';
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
	connections.insert(pair<int, TCPStream*>(stream->GetSocket(), stream));
	cout << "Added socket " << stream->GetSocket() << " to the connection list." << '\n';
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
	delete listener;
	listener = nullptr;
}