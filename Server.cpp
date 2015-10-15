#include "Server.h"
#include "TCPListener.h"
#include <map>
#include <iostream>

#include <Windows.h>
#include <tchar.h.>
#include <strsafe.h>


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
	const int MAX_THREADS = 2;

	HANDLE hThreadArray[MAX_THREADS];
	DWORD dwThreadIdArray[MAX_THREADS];

	hThreadArray[0] = CreateThread(
		NULL,
		0,
		Server::CreateMessageQueueThread,
		this,
		0,
		&dwThreadIdArray[0]);

	hThreadArray[1] = CreateThread(
		NULL,
		0,
		TCPListener::CreateListenerThread,
		listener,
		0,
		&dwThreadIdArray[1]);

	if (hThreadArray[0] == NULL) {
		ErrorHandler("Create thread failed for Message Queue.");
		ExitProcess(3);
	}
	if (hThreadArray[1] == NULL) {
		ErrorHandler("Create thread failed for Listener.");
		ExitProcess(3);
	}
	
	WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);

	CloseHandle(hThreadArray[0]);
	CloseHandle(hThreadArray[1]);

	// listener->Listen();
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

DWORD WINAPI Server::CreateMessageQueueThread(void* arg) {
	Server* instance = (Server*)arg;
	instance->HandleMessageQueue();
	return 0;
}