#pragma once

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else // _WIN32
    #include <sys/socket.h>
#endif

#include "Connection.hpp"
#include "ConnectionList.hpp"

#include <vector>

#define DEFAULT_PORT "4000"
#define MAX_PORT_LENGTH 6
#define MAX_CONNECTIONS 100

class ConnectionList;

class Server {
public:
    Server();
    Server(int port);
    int Listen();
    int Close();
    int CheckForNewConnections();


protected:
    int HandleConnection();
    char* port;
    int listenSocket;
    ConnectionList* connections;
};
