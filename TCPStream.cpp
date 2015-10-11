#include "TCPStream.h"

using namespace std;

TCPStream::TCPStream(int socketfd, struct sockaddr_in* address) {
    char ip[50];
    //socklen_t addr_len = sizeof(address);
    //getnameinfo((struct sockaddr*)&address,addr_len,ip,sizeof(ip), 0,0,NI_NUMERICHOST);
    inet_ntop(PF_INET, (struct in_addr*)&(address->sin_addr.s_addr), ip, sizeof(ip)-1);
    peerIP = ip;
    peerPort = ntohs(address->sin_port);
}

TCPStream::TCPStream() {

}

TCPStream::TCPStream(const TCPStream& stream) {

}

TCPStream::~TCPStream() {
    #ifdef _WIN32
        closesocket(socketfd);
    #else
        close(socketfd);
    #endif // _WIN32
}

ssize_t TCPStream::send(char* buffer, size_t len) {
    return write(socketfd, buffer, len);
}

ssize_t TCPStream::receive(char* buffer, size_t len, int timeout) {
    if (timeout <= 0) return read(socketfd, buffer, len);

    if (waitForReadEvent(timeout) == true)
    {
        return read(socketfd, buffer, len);
    }
    return connectionTimedOut;
}

string TCPStream::getPeerIP() {
    return peerIP;
}

int TCPStream::getPeerPort() {
    return peerPort;
}

int TCPStream::getSocket() {
    return socketfd;
}

bool TCPStream::waitForReadEvent(int timeout)
{
    fd_set sdset;
    struct timeval tv;

    tv.tv_sec = timeout;
    tv.tv_usec = 0;
    FD_ZERO(&sdset);
    FD_SET(socketfd, &sdset);
    if (select(socketfd+1, &sdset, NULL, NULL, &tv) > 0)
    {
        return true;
    }
    return false;
}
