#include "ConnectionList.hpp"
#include "Connection.hpp"
#include "Server.hpp"

#include <queue>
#include <iostream>

using namespace std;

ConnectionList::ConnectionList() {
    this->connections = nullptr;
    this->connectionCount = 0;
}


int ConnectionList::AddConnection(Connection* con) {
    cout << "Adding connection." << '\n';
    if (connectionCount == 0) {
        cout << "No connections so far." << '\n';
        connections = con;
        cout << "Added first connection." << '\n';
        ++connectionCount;
        cout << "Incremented connectionCount." << '\n';
        FD_SET(con->GetTCPStream()->getSocket(), &sockets);
        return 0;
    }

    Connection* current = connections;
    for (int i = 0; i < connectionCount; ++i) {
        current = current->GetNext();
    }
    current->SetNext(con);
    ++connectionCount;


    return 0;
}

Connection* ConnectionList::GetConnection(int index) {
    Connection* con = connections;
    for (int i = 0; i <= index; i--) {
        if (con->GetNext()) {
            con = con->GetNext();
        }
    }
    return con;
}

int ConnectionList::RemoveConnection(int index) {
    Connection* con = connections;
    Connection* prev = con;
    for (int i = 0; i <= index; i--) {
        prev = con;
        con = con->GetNext();
    }
    prev->SetNext(con->GetNext());
    FD_CLR(con->GetTCPStream()->getSocket(), &sockets);
    delete con;
    return 0;
}

int ConnectionList::GetConnectionCount() {
    return connectionCount;
}

void ConnectionList::Receive() {
    Connection* current = connections;
    for (int i = 0; i < connectionCount; ++i) {
        if (current->Read() != 0 && current->GetBuffer() != "") {
            cout << current->GetTCPStream()->getPeerIP() << '\n';
            current->PrintBuffer();
            current = current->GetNext();
        }
    }
}
