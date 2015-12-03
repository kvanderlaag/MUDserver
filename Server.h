#pragma once

#include "TCPListener.h"
#include "MessageBuffer.h"
#include <map>
#ifdef _WIN32
#include <Windows.h>
#endif
#include "GameWorld.h"
#include "FileParser.h"
#include "Parser.h"
#include <string>
#include <thread>

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

	void PutMessage(Message* mess);

	TCPListener* GetListener() const;
    bool IsRunning() const;

private:
	bool running;

	std::unique_ptr<Parser> parser;

	std::unique_ptr<GameWorld> world;
	std::unique_ptr<TCPListener> listener;
	std::map<int, TCPStream*> connections;
	std::unique_ptr<MessageBuffer> mBuffer;

	std::string mLoginMessage;

	std::unique_ptr<std::thread> listenerThread;
	std::unique_ptr<std::thread> messageQueueThread;

	Message* ParseMessage(Message*);
	void SendLoginMessage(TCPStream* stream);
};
