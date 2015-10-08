#pragma once

#include <queue>

#include "Server.hpp"
#include "Connection.hpp"

#ifndef MAX_CONNECTIONS
#define MAX_CONNECTIONS 5
#endif

class ConnectionList {
public:
    ConnectionList();

    int AddConnection(Connection* con);
    Connection *GetConnection(int index);

protected:
    Connection *connections[MAX_CONNECTIONS];
    std::deque <int> freeConnections;
};
