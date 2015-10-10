#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#define MAX_CONNECTION_BUFFER 50

#include "TCPStream.h"
#include <string>

class Connection {
public:
    Connection(TCPStream* con);
    ~Connection();
    int Close();
    TCPStream* GetTCPStream();
    int Read();
    void PrintBuffer();
    Connection* GetNext();
    int SetNext(Connection* con);

protected:
    TCPStream* stream;
    Connection* next;
    string buffer;

};

#endif // __CONNECTION_H__
