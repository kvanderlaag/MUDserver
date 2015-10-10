#include "ConnectionList.hpp"
#include "Connection.hpp"
#include "Server.hpp"

#include <queue>
#include <iostream>

using namespace std;

ConnectionList::ConnectionList() {
    connections = (Connection**) malloc(sizeof (Connection*) * MAX_CONNECTIONS);
    for (int i = 0; i < MAX_CONNECTIONS; ++i) {
        this->connections[i] = nullptr;
    }
}


int ConnectionList::AddConnection(Connection* con) {
    return -1;
}

Connection* ConnectionList::GetConnection(int index) {
    return this->connections[index];
}

int ConnectionList::CloseAll() {

    return 0;
}
