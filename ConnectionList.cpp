#include "ConnectionList.hpp"
#include "Connection.hpp"
#include "Server.hpp"

#include <queue>
#include <iostream>

using namespace std;

ConnectionList::ConnectionList() {
    for (int i = 0; i < MAX_CONNECTIONS; ++i) {
        this->connections[i] = nullptr;
    }
}


int ConnectionList::AddConnection(Connection* con) {
    for (int i = 0; i < MAX_CONNECTIONS; ++i) {
        if (this->connections[i] == nullptr) {
                this->connections[i] = con;
                FD_SET(con->GetSocket(), &this->sockets);
                if (con->GetSocket() > this->maxsocket) {
                    this->maxsocket = con->GetSocket();
                }
                return 0;
        }
    }
    cout << "Unable to add connection to ConnectionList." << '\n';
    return -1;
}

Connection* ConnectionList::GetConnection(int index) {
    return this->connections[index];
}

int ConnectionList::CloseAll() {
    for (int i = 0; i < MAX_CONNECTIONS; ++i) {
        if (this->connections[i] != nullptr) {
            #ifdef _WIN32
                int status = closesocket(this->connections[i]->GetSocket());
            #else
                int status = close(this->connections[i]->GetSocket());
            #endif // _WIN32

            if (status == -1) {
                cout << "Failed to close socket " << this->connections[i]->GetSocket() << '\n';
            }
        }
    }
    return 0;
}
