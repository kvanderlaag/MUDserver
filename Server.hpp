#ifdef _WIN32

#include <winsock2.h>
#include <ws2tcpip.h>

#else // _WIN32

#include <sys/socket.h>

#endif

#define DEFAULT_PORT "4000"
#define MAX_PORT_LENGTH 6

class Server {
public:
    Server();
    Server(int port);
    int Listen();
    int Close();


protected:
    int HandleConnection();
    char* port;
    int listenSocket;

};
