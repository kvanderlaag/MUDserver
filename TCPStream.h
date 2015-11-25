#pragma once

#include "TCPListener.h"
#include "Server.h"

#include "event2/event.h"
#include "event2/buffer.h"
#include "event2/bufferevent.h"

#include <string>

class TCPListener;
class Server;

class TCPStream
{
public:
	TCPStream(TCPListener* par, int socket);
	~TCPStream();

	void read_cb(struct bufferevent *bev);
	void write_cb(struct bufferevent * bev);
	void error_cb(bufferevent *bev, short error);

	const int GetSocket();
	const int Write(std::string outputMessage);

	static void do_error(struct bufferevent *bev, short error, void* arg);

	static void do_read(struct bufferevent *bev, void* arg);
	static void do_write(struct bufferevent *bev, void* arg);

private:
	bufferevent* bEvent;
	TCPListener* parent;
	int socketfd;
	std::string buffer;

};

