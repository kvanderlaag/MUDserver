#include "ConnectionList.hpp"
#include "Connection.hpp"
#include "Server.hpp"

#include <queue>

ConnectionList::ConnectionList() {
    for (int i = 0; i < MAX_CONNECTIONS; ++i) {
        this->connections[i] = NULL;
        this->freeConnections.push_back(i);
    }
}


int ConnectionList::AddConnection(Connection* con) {
    int index = this->freeConnections.front();
    this->freeConnections.pop_front();

    connections[index] = con;

    return 0;
}
