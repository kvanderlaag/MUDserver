#ifndef __CONNECTIONLIST_H__
#define __CONNECTIONLIST_H__

#include "Connection.hpp"

#include <sys/time.h>
#include <sys/types.h>
#include <sys/unistd.h>

class ConnectionList {
public:
    ConnectionList();

    int AddConnection(Connection* con);
    int CloseAll();
    Connection *GetConnection(int index);

protected:
    Connection **connections;
    fd_set sockets;
    int maxsocket;
};

#endif
