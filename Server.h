#pragma once

#include "TCPListener.h"
#include "MessageBuffer.h"
#include <map>
#include <Windows.h>
#include "GameWorld.h"
#include "Parser.h"

class TCPListener;
class TCPStream;
class GameWorld;

/**
* Header file for server
*/
class Server
{
public:
	Server(int port=9500);
	~Server();

	int AddConnection(TCPStream* stream);
	int RemoveConnection(TCPStream* stream);

	void Start();
	void Shutdown();

	static void CreateMessageQueueThread(void* arg);
	static void CreateListenerThread(void* arg);
	void HandleMessageQueue();
	void ErrorHandler(const std::string arg);

	void PutMessage(const Message* mess);

private:
	bool running;

	Parser* parser;
	Message* ParseMessage(const Message&);

	GameWorld* world;
	TCPListener* listener;
	std::map<int, TCPStream*> connections;
	MessageBuffer* mBuffer;


};
