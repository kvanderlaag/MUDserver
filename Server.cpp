#ifdef _WIN32

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x6000
#endif // _WIN32_WINNT

#include <winsock2.h>
#include <ws2tcpip.h>

#else // _WIN32

#include <sys/socket.h>

#endif

#ifndef _SERVER_H
#include "Server.hpp"
#endif // _SERVER_H

#include <iostream>

using namespace std;

Server::Server() {
    this->port = (char*) malloc(sizeof (char) * MAX_PORT_LENGTH);
    strcpy(this->port, DEFAULT_PORT);
    cout << "Attempting to start server on port " << this->port << '\n';
    if (this->Listen() != 0) {
        cout << "Failed to listen on port " << port << ". Server in idle state." << '\n';
    };

}

Server::Server(int port) {
    this->port = (char*) malloc(sizeof (char) * MAX_PORT_LENGTH);
    itoa(port, this->port, 10);
    cout << "Attempting to start server on port " << this->port << '\n';
    if (this->Listen() != 0) {
        cout << "Failed to listen on port " << port << ". Server in idle state." << '\n';
    };

}

int Server::Listen() {

    #ifdef _WIN32
    WSAData wsaData;
    int iResult = 0;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        cout << "WSAStartup failed.";
        return -1;
    }

    #endif // _WIN32

    struct addrinfo hints, *res;
    int status;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    status = getaddrinfo(NULL, this->port, &hints, &res);
    if (status != 0) {
        cout << "Error getting address info." << '\n';
        cout << gai_strerror(status) << '\n';
        return -1;
    }

    this->listenSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (this->listenSocket == INVALID_SOCKET) {
        cout << "Error creating socket for server." << '\n';
        return -1;
    }

    status = bind(this->listenSocket, res->ai_addr, res->ai_addrlen);
    if (status == SOCKET_ERROR) {
        cout << "Error binding socket for server." << '\n';
        return -1;
    }

    cout << "Server listening on port " << this->port << '\n';
    return 0;
}

int Server::Close() {
    if (this->listenSocket) {
        #ifdef _WIN32
            int closed = closesocket(this->listenSocket);
        #else
            int closed = close(this->listenSocket);
        #endif // _WIN32

        if (closed != 0) {
            cout << "Error closing socket on server." << '\n';
            return -1;
        } else {
            cout << "Server no longer listening on port " << this->port << '\n';
            return 0;
        }
    }
    cout << "Error closing socket: Socket was never open.\n";
    return -1;
}

int Server::CheckForNewConnections() {

    int addrlen;
    struct sockaddr addrinfo;
    addrlen = sizeof addrinfo;

    int newsock;

    if ((newsock = accept(this->listenSocket, &addrinfo, &addrlen)) == -1) {
        //cout << "Error accepting incoming connection. Error: " << WSAGetLastError() << '\n';
        return -1;
    } else {
        this->connections->AddConnection(new Connection(&addrinfo, newsock));
        cout << "Accepted new connection." << '\n';
    }

    return 0;
}
