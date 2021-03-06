#include "Server.h"
#include "TCPListener.h"
#include <map>
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#include <tchar.h.>
#include <strsafe.h>
#endif


/**
* Creates a server on a given port number
* Creates a listener on that port
* Creates a new game world
* Creates a message buffer for new messages to get read and written to
*/
Server::Server(int port)
	: listener(new TCPListener(this))
	, world(new GameWorld(*this))
	, mBuffer(new MessageBuffer())
	, running(false)
	, parser(new Parser())
	, mLoginMessage("Welcome to JakeMUD!\n\nCommands:\nlogin <username> <password>\nsignup <username> <password>\n\n(Passwords are stored plaintext; please use caution.)\n")
{
	std::cout << "Creating new Server on port " << port << ".\n";
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
   std::cout << "Destroying server.\n";
//	world.reset();
//	listener.reset();
//	parser.reset();
//	mBuffer.reset();
//	listenerThread.reset();
//	messageQueueThread.reset();
}

/**
* Begin running the srever
* Create a thread for listeners and message buffer
* Will now listen for messages and connections from users
*/
void Server::Start()
{
	running = true;

	listenerThread = std::unique_ptr<std::thread>(new std::thread(&CreateListenerThread, listener.get()));
	messageQueueThread = std::unique_ptr<std::thread>(new std::thread(&CreateMessageQueueThread, this));
	world.get()->StartUpdate();
	//listenerThread.get()->join();
	messageQueueThread.get()->join();
}

TCPListener* Server::GetListener() const {
	return listener.get();
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
	listener.get()->ShutdownListener();
	listenerThread.release();
	messageQueueThread.release();
	world.get()->ReleaseThreads();
	//listener.release();
	//world.release();
}

/**
* Place a new message onto the message buffer
*/
void Server::PutMessage(Message* mess)
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
	std::cout << "Message Queue handler terminated." << '\n';
}

/**
* Parse a message from the server.
*/
Message* Server::ParseMessage(Message* mess) {
	Message* returnMessage = parser->Parse(mess);
	mBuffer->PutMessage(returnMessage);
	delete mess;
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

bool Server::IsRunning() const {
	return running;
}

GameWorld& Server::GetWorld() {
	return *(world.get());
}