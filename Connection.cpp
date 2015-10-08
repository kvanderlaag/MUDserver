
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
