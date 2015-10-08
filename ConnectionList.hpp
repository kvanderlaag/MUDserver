#pragma once

#include <queue>

#include "Connection.hpp"
#include "Server.hpp"

#ifndef MAX_CONNECTIONS
#define MAX_CONNECTIONS 100
#endif

class ConnectionList {
public:
    ConnectionList();

    int AddConnection(Connection* con);

protected:
    Connection *connections[MAX_CONNECTIONS];
    std::deque <int> freeConnections;
};
