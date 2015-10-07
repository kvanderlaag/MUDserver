#ifdef _WIN32

#include <winsock2.h>
#include <ws2tcpip.h>

#else // _WIN32

#include <sys/socket.h>

#endif

class Connection {

    public:
        Connection();
        int Listen(int port);

    protected:
        int *port;
        struct addrinfo *host;

};
