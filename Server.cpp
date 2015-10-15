#include "Server.h"
#include "TCPListener.h"
#include <map>
#include <iostream>

#include <Windows.h>
#include <tchar.h.>
#include <strsafe.h>
#include <thread>


Server::Server(int port)
	: listener(new TCPListener(this))
	, world(new GameWorld())
	, mBuffer(new MessageBuffer())
	, running(false)
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
	running = true;

	std::thread listenerThread (&CreateListenerThread, listener);
	std::thread messageQueueThread (&CreateMessageQueueThread, this);

	listenerThread.join();
	messageQueueThread.join();
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
	running = false;
	for (int i = 0; i < connections.size(); ++i) {
		RemoveConnection(connections.begin()->second);
	}
	delete listener;
	listener = nullptr;
}

void Server::PutMessage(const Message& mess) {
	mBuffer->PutMessage(mess);
}

void Server::HandleMessageQueue() {
	while (running) {
		if (!mBuffer->IsEmpty()) {
			Message* mess = (Message*) mBuffer->DequeueMessage();
			std::cout << "Message type: " << mess->GetType() << ", Message: " << mess->Read() << '\n';
		}
	}
	std::cout << "Message Queue handler terminated." << '\n';
}

void Server::ErrorHandler(const std::string arg) {
	std::cout << arg << '\n';
}

void Server::CreateMessageQueueThread(void* arg) {
	Server* instance = (Server*)arg;
	instance->HandleMessageQueue();
}

void Server::CreateListenerThread(void* arg) {
	TCPListener* instance = (TCPListener*)arg;
	instance->Listen();
}
