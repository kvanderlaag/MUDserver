#include "Server.h"
#include "TCPListener.h"
#include <map>
#include <iostream>

#include <Windows.h>
#include <tchar.h.>
#include <strsafe.h>

/**
* Creates a server on a given port number
* Creates a listener on that port
* Creates a new game world
* Creates a message buffer for new messages to get read and written to
*/
Server::Server(int port)
	: listener(new TCPListener(this))
	, world(new GameWorld(this))
	, mBuffer(new MessageBuffer())
	, running(false)
	, parser(new Parser())
	, mLoginMessage("Welcome to JakeMUD!\n\r\n\rCommands:\n\rlogin <username> <password>\n\rsignup <username> <password>\n\r")
{
	std::cout << "Creating new Server on port " << port << ".\n\r";
#ifdef _DEBUG_FLAG
	std::cout << "TCPListener creation successful." << "\n\r";
#endif
}

/**
* Destroys the server
* Destroy the listener
* Destroy the message buffer
*/
Server::~Server()
{
	if (listener)
	{
		delete listener;
	}
	if (mBuffer)
	{
		delete mBuffer;
	}
}

/**
* Begin running the srever
* Create a thread for listeners and message buffer
* Will now listen for messages and connections from users
*/
void Server::Start()
{
	running = true;

	listenerThread = new std::thread(&CreateListenerThread, listener);
	messageQueueThread = new std::thread(&CreateMessageQueueThread, this);

	listenerThread->join();
	messageQueueThread->join();
}

TCPListener* Server::GetListener() {
	return listener;
}

/**
* Add a new connection to the server when a user connects
*/
int Server::AddConnection(TCPStream* stream)
{
	connections.insert(std::pair<int, TCPStream*>(stream->GetSocket(), stream));
#ifdef _DEBUG_FLAG
	std::cout << "Added socket " << stream->GetSocket() << " to the connection list." << '\n';
#endif
	SendLoginMessage(stream);
	return 0;
}

/**
* Remove a connection from the connection list
*/
int Server::RemoveConnection(TCPStream* stream)
{
	int status = connections.erase(stream->GetSocket());
	if (status)
	{
		world->LogOut(stream->GetSocket());
		delete stream;
	}
	return status;

}

/**
* Stops the server
* Remove all connected users
* Destroy the listener
*/
void Server::Shutdown()
{
	running = false;
	for (std::size_t i = 0; i < connections.size(); ++i)
	{
		RemoveConnection(connections.begin()->second);
	}
	delete listener;
	listener = nullptr;
	delete world;
	world = nullptr;
	
	
}

/**
* Place a new message onto the message buffer
*/
void Server::PutMessage(const Message* mess)
{
	mBuffer->PutMessage(mess);
}

/**
* Checks if therea is a message in the message buffer
* If so, removes the message and sends it to the parser
*/
void Server::HandleMessageQueue()
{
	while (running)
	{
		if (!mBuffer->IsEmpty())
		{
			Message* mess = (Message*) mBuffer->DequeueMessage();
#ifdef _DEBUG_FLAG
			std::cout << "Message type: " << mess->GetType() << /*", Message: " << mess->Read() <<*/ " - Connection ID: " << mess->GetSource() << '\n';
#endif
			if (mess->GetType() == Message::MessageType::inputMessage) 
				mBuffer->PutMessage(parser->Parse(mess));
			else if (mess->GetType() == Message::MessageType::outputMessage) {
#ifdef _DEBUG_FLAG
				std::cout << "Writing message out to " << mess->GetSource() << std::endl;
#endif
				std::map<int, TCPStream*>::iterator it;
				it = connections.find(mess->GetSource());
				if (it != connections.end()) {
					it->second->Write(mess->Read());
				}
			}
			else if (mess->GetType() == Message::MessageType::gameActionMessage) {
				world->ReceiveMessage(mess);
			}

		}
	}
#ifdef _DEBUG_FLAG
	std::cout << "Message Queue handler terminated." << '\n';
#endif
}

/**
* Parse a message from the server.
*/
Message* Server::ParseMessage(const Message& mess) {
	Message* returnMessage = parser->Parse(&mess);
	mBuffer->PutMessage(returnMessage);
	return returnMessage;
	
}

/**
* Prints out any errors
*/
void Server::ErrorHandler(const std::string arg)
{
#ifdef _DEBUG_FLAG
	std::cout << arg << '\n';
#endif
}

/**
* Create a new message buffer thread
* Multithreads incoming messages
*/
void Server::CreateMessageQueueThread(void* arg)
{
	Server* instance = (Server*)arg;
	instance->HandleMessageQueue();
}

/**
* Create a new listener thread
* Multithreads conencting users
*/
void Server::CreateListenerThread(void* arg)
{
	TCPListener* instance = (TCPListener*)arg;
	instance->Listen();
}

void Server::SendLoginMessage(TCPStream* stream) {
	stream->Write(mLoginMessage);
}
