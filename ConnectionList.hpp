#pragma once

#include "Server.hpp"
#include "Connection.hpp"

#include <sys/time.h>
#include <sys/types.h>
#include <sys/unistd.h>

#ifndef MAX_CONNECTIONS
#define MAX_CONNECTIONS 5
#endif

class ConnectionList {
public:
    ConnectionList();

    int AddConnection(Connection* con);
    int CloseAll();
    Connection *GetConnection(int index);

protected:
    Connection *connections[MAX_CONNECTIONS];
    fd_set sockets;
    int maxsocket;
};
