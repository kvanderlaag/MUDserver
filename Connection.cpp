#include "Connection.hpp"
#include <iostream>

Connection::Connection(TCPStream* con) {
    stream = con;
    buffer = "";
    next = nullptr;
}

Connection::~Connection() {
    delete stream;
}

TCPStream* Connection::GetTCPStream() {
    return stream;
}

int Connection::Read() {
    char* buff = (char*) malloc(MAX_CONNECTION_BUFFER);
    memset(buff, 0, MAX_CONNECTION_BUFFER);
    stream->receive(buff, MAX_CONNECTION_BUFFER, 0);
    buffer += buff;
    int len = strlen(buff);
    free(buff);
    return len;
}

int Connection::Close() {
    delete stream;
    return 0;
}

void Connection::PrintBuffer() {
    cout << buffer << '\n';
    buffer = "";
}

Connection* Connection::GetNext() {
    return next;
}

int Connection::SetNext(Connection* con) {
    next = con;
    return 0;
}
