// MUDServer_libevent.cpp : Defines the entry point for the console application.
//

#include "Server.h"

#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#else
#include <sys/socket.h>
#endif

#include <cstdio>
#include <iostream>
#include <memory>

using namespace std;

#ifdef _WIN32
/*
	WinsockStart()

	Utility function for initializing Winsock on Windows systems.

*/
int WinsockStart()
{
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (iResult != 0)
	{
		std::cout << "Shitty WSAStartup. Exiting.";
	}
	return iResult;
}
#endif


/**
* main() function. Starts up Winsock if necessary, creates a new server,
* and starts it listening on the default port.
*/
int main(int argc, char** argv)
{

	setvbuf(stdout, NULL, _IONBF, 0);

#ifdef _WIN32
	if (WinsockStart() != 0)
	{
		std::cout << "Could not initialize Winsock." << '\n';
		return -1;
	}
#endif

	std::unique_ptr<Server> gameServer = std::unique_ptr<Server>(new Server());
	gameServer.get()->Start();

	gameServer.reset();
	cout << "Server terminated. Any key to exit.";
	fgetc(stdin);

	return 0;
}
