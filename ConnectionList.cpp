#include "ConnectionList.hpp"
#include "Connection.hpp"
#include "Server.hpp"

#include <queue>
#include <iostream>

using namespace std;

ConnectionList::ConnectionList() {
    connections = (Connection**) malloc(sizeof (Connection*) * MAX_CONNECTIONS);
    memset(connections, 0, sizeof(Connection*) * MAX_CONNECTIONS);
    connectionCount = 0;
}


int ConnectionList::AddConnection(Connection* con) {
    for (Connection* current = connections; current->GetNext() != nullptr; current = current->GetNext()) {
            if (current->GetNext() == nullptr) {
                current->SetNext(con);
                return 0;
            }
    }

    return -1;
}

Connection* ConnectionList::GetConnection(int index) {
    return connections[index];
}

int ConnectionList::CloseAll() {

    return 0;
}

int ConnectionList::GetConnectionCount() {
    return connectionCount;
}
