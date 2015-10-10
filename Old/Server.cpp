#include "Server.hpp"

#include <iostream>
#include <cstdio>

using namespace std;

Server::Server() {
    this->port = (char*) malloc(sizeof (char) * MAX_PORT_LENGTH);
    sprintf(this->port, DEFAULT_PORT);

    FD_ZERO(&this->listener);
    this->fdmax = 0;

    cout << "Attempting to start server on port " << this->port << '\n';
    if (this->Listen() != 0) {
        cout << "Failed to listen on port " << port << ". Server in idle state." << '\n';
    this->connections = new ConnectionList();


    };

}

Server::Server(int port) {
    this->port = (char*) malloc(sizeof (char) * MAX_PORT_LENGTH);
    sprintf(this->port, "%d", port);

    FD_ZERO(&this->listener);
    this->fdmax = 0;

    cout << "Attempting to start server on port " << this->port << '\n';
    if (this->Listen() != 0) {
        cout << "Failed to listen on port " << port << ". Server in idle state." << '\n';
    };
    this->connections = new ConnectionList();

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
    hints.ai_family = AF_INET;  // use IPv4 or IPv6, whichever
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    status = getaddrinfo(NULL, this->port, &hints, &res);
    if (status != 0) {
        cout << "Error getting address info." << '\n';
        //cout << gai_strerror(status) << '\n';
        return -1;
    }

    this->listenSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (this->listenSocket < 0) {
        cout << "Error creating socket for server." << '\n';
        return -1;
    }

    status = bind(this->listenSocket, res->ai_addr, res->ai_addrlen);
    if (status != 0) {
        cout << "Error binding socket for server." << '\n';
        #ifdef _WIN32
            closesocket(this->listenSocket);
        #else
            close(this->listenSocket);
        #endif // _WIN32
        return -1;
    }

    status = listen(this->listenSocket, MAX_CONNECTIONS);
    if (status != 0) {
        cout << "Error listening on port " << this->port << '\n';
        return -1;
    }

    //freeaddrinfo(res);

    cout << "Server listening on port " << this->port << '\n';

    FD_SET(this->listenSocket, &this->listener);
    if (this->listenSocket > this->fdmax) {
        this->fdmax = this->listenSocket;
    }

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
            this->connections->CloseAll();
            return 0;
        }
    }
    cout << "Error closing socket: Socket was never open.\n";
    return -1;
}

int Server::CheckForStdInput() {
    timeval tv;

    tv.tv_sec = 0;
    tv.tv_usec = 0;

    fd_set stdinput, read_fds;
    FD_ZERO(&stdinput);
    FD_ZERO(&read_fds);
    FD_SET(0, &stdinput);

    read_fds = stdinput;

    if (select(this->fdmax, &read_fds, NULL, NULL, &tv) == -1) {
        cout << "Select error in getting std input." << '\n';
        return -1;
    }
    return 0;
}

int Server::CheckForNewConnections() {

    timeval tv;

    tv.tv_sec = 0;
    tv.tv_usec = 0;

    fd_set fdlist;
    FD_ZERO(&fdlist);

    fdlist = this->listener;

    if (select(this->fdmax+1, &fdlist, NULL, NULL, &tv) == -1) {
        cout << "Error: select()." << '\n';
        return -1;
    }

    if (FD_ISSET(0, &fdlist)) {
        char* buffer = (char*) malloc(MAX_BUFFER_LENGTH);
        fgets(buffer, MAX_BUFFER_LENGTH, stdin);
        cout << buffer;

    }

    if (FD_ISSET(this->listenSocket, &fdlist)) {
            int addrlen;
            sockaddr_storage extsocket;
            addrlen = sizeof extsocket;
            int newsock;
            cout << "Waiting to accept: " << '\n';
            newsock = accept(this->listenSocket, (sockaddr*) &extsocket, &addrlen);
            cout << "2";
            if (newsock < 0) {
                cout << "newsock < 0";
                #ifdef _WIN32
                if (WSAGetLastError() != 10022) {
                    return -1;
                } else {
                cout << "Error accepting incoming connection";
                cout << "Error accepting incoming connection. Error: " << WSAGetLastError() << '\n';
                }
                #endif
            } else {
                cout << "Create new connection.";
                Connection* con = new Connection( (sockaddr*) &extsocket, newsock);
                cout << "if connections->AddConnection(con) != -1";
                if (this->connections->AddConnection(con) != -1) {
                        cout << "Accepted new connection." << '\n';
                } else {
                    cout << "Couldn't accept new connection.";
                    con->Close();
                }

            }

    }
    return 0;

}

int Server::ReceiveConnections() {
    cout << "Receiving connections." << '\n';
    for (int i = 0; i < MAX_CONNECTIONS; ++i) {
        Connection* con = this->connections->GetConnection(i);
        char* buffer = (char*) malloc (sizeof (char) * MAX_BUFFER_LENGTH);
        if (con != nullptr) {
            recv(con->GetSocket(), buffer, MAX_BUFFER_LENGTH, 0);
            cout << buffer;
        }
    }

    return 0;
}
