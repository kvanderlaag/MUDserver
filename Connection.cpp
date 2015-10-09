
#ifdef _WIN32

#include <winsock2.h>
#include <ws2tcpip.h>

#else // _WIN32

#include <sys/socket.h>

#endif

#include "Connection.hpp"

Connection::Connection(struct sockaddr* host, int socketfd) {
    this->host = host;
    this->socketfd = socketfd;
}

Connection::~Connection() {
    if (this->socketfd != -1) {
        #ifdef _WIN32
            closesocket(this->socketfd);
        #else
            close(this->socketfd);
        #endif // _WIN32
    }
    free(this->host);
}

int Connection::GetSocket() {
    return this->socketfd;
}

int Connection::Close() {
    #ifdef _WIN32
        closesocket(this->socketfd);
    #else
        close(this->socketfd);
    #endif // _WIN32
    this->socketfd = -1;
    this->host = nullptr;
    return 0;
}
