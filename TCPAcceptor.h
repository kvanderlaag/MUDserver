#ifndef __TCPACCEPTOR_H__
#define __TCPACCEPTOR_H__

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
#include "TCPStream.h"

using namespace std;

class TCPAcceptor
{
    int    m_lsd;
    int    m_port;
    string m_address;
    bool   m_listening;

  public:
    TCPAcceptor(int port, const char* address="");
    ~TCPAcceptor();

    int        start();
    TCPStream* accept();
    bool waitForConnectEvent(int timeout);

  private:
    TCPAcceptor() {}
};

#endif
