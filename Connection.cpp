#include "Connection.hpp"
#include <iostream>

Connection::Connection(TCPStream* con) {
    stream = con;
    buffer = "";
    next = nullptr;
}

Connection::~Connection() {

}

TCPStream* Connection::GetTCPStream() {
    return stream;
}

int Connection::Read() {
    char* buff = (char*) malloc(MAX_CONNECTION_BUFFER);
    buffer += stream->receive(buff, MAX_CONNECTION_BUFFER, 0);
    int len = strlen(buff);
    free(buff);
    return len;
}

int Connection::Close() {
    delete stream;
    return 0;
}

void Connection::PrintBuffer() {
    cout << buffer;
}

Connection* GetNext() {
    return next;
}

int SetNext(Connection* con) {
    next = con;
    return 0;
}
