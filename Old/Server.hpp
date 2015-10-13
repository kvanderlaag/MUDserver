#ifndef __SERVER_H__
#define __SERVER_H__

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else // _WIN32
    #include <sys/socket.h>
#endif

#include "Connection.hpp"

#include "ConnectionList.hpp"
#include "TCPAcceptor.h"

#include <sys/time.h>
#include <sys/types.h>
#include <sys/unistd.h>

#include <vector>

#define DEFAULT_PORT "4000"
#define MAX_PORT_LENGTH 6
#define MAX_CONNECTIONS 5
#define MAX_BUFFER_LENGTH 100


class Server {
public:
    Server(int port=4500);
    ~Server();
    int Listen();
    int Close();
    int CheckForNewConnections();
    int ReceiveConnections();
    int CheckForStdInput();


protected:
    int HandleConnection();
    int port;
    TCPAcceptor* listener;
    ConnectionList* connections;
};

#endif // __SERVER_H__
