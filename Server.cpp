#include "Server.hpp"

#include <iostream>
#include <cstdio>

using namespace std;

Server::Server(int port) {
    #ifdef _WIN32
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        cout << "Could not initialize Winsock" << '\n';
    }
    #endif

    this->port = port;
    listener = new TCPAcceptor(port);
}

Server::~Server() {
    delete listener;
}

int Server::Listen() {
    int status = listener->start();
    if (status == 0) {
        cout << "Listening on port " << port << '\n';
    } else {
        cout << "Error listening on port " << port << ". Status: " << status << '\n';
    }
    return status;

}

int Server::Close() {
    return 0;
}

int Server::CheckForStdInput() {
    return 0;
}

int Server::CheckForNewConnections() {
    TCPStream* newConnection;
    if (listener->waitForConnectEvent(0)) {
        newConnection = listener->accept();
        if (newConnection) {
            Connection* con = new Connection(newConnection);
            if (connections->AddConnection(con) == 0) {
                cout << "Accepted connection." << '\n';
            } else {
                cout << "Could not accept connections. Maximum connections reached." << '\n';
            }


        }
    }
    return 0;
}

int Server::ReceiveConnections() {

    return 0;
}
