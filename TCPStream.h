#ifndef __TCPSTREAM_H__
#define __TCPSTREAM_H__


#ifdef _WIN32

#include <winsock2.h>
#include <ws2tcpip.h>
#include "wsinet.h"

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x6000
#endif // _WIN32_WINNT

#else

#include <sys/socket.h>

#endif // _WIN32

#include <sys/types.h>
#include <sys/unistd.h>
#include <string>

using namespace std;

class TCPStream{
    int socketfd;
    int peerPort;
    string peerIP;
public:
    friend class TCPAcceptor;

    ~TCPStream();
    ssize_t send(char* buffer, size_t len);
    ssize_t receive(char* buffer, size_t len, int timeout=0);

    string getPeerIP();
    int getPeerPort();

    enum {
        connectionClosed = 0,
        connectionReset = -1,
        connectionTimedOut = -2
    };

private:
    bool waitForReadEvent(int timeout);

    TCPStream(int sd, struct sockaddr_in* address);
    TCPStream();
    TCPStream(const TCPStream& stream);
};

#endif // __TCPSTREAM_H__
