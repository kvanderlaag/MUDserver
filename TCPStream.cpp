#include "TCPStream.h"
#include "Message.h"

#include <iostream>



TCPStream::TCPStream(TCPListener* par, int socket)
	: parent(par)
	, socketfd(socket)
	, bEvent(bufferevent_socket_new((event_base*) par->GetBase(), socket, BEV_OPT_CLOSE_ON_FREE))
{
	evutil_make_socket_nonblocking(socketfd);
	std::cout << "Socket " << socketfd << " is nonblocking." << '\n';

	std::cout << "Made new buffer event." << '\n';
	bufferevent_setcb(bEvent, do_read, do_write, do_error, (void*)this);
	std::cout << "Set read callback and error callback." << '\n';
	bufferevent_setwatermark(bEvent, EV_READ, 0, MAX_LINE);
	std::cout << "Set watermark." << '\n';
	bufferevent_enable(bEvent, EV_READ | EV_WRITE);
	std::cout << "Enabled buffer event." << '\n';
}


TCPStream::~TCPStream()
{
	bufferevent_free(bEvent);
	std::cout << "Closing socket " << socketfd << '\n';
	std::cout << "Removed socket " << socketfd << " from connection list." << '\n';
}

void TCPStream::do_error(struct bufferevent *bev, short error, void* arg) {
	(static_cast<TCPStream*>(arg))->error_cb(bev, error);
}

void TCPStream::do_read(struct bufferevent *bev, void* arg) {
	(static_cast<TCPStream*>(arg))->read_cb(bev);
}

void TCPStream::do_write(struct bufferevent *bev, void* arg) {
	(static_cast<TCPStream*>(arg))->write_cb(bev);
}

void TCPStream::read_cb(struct bufferevent *bev) {
	evbuffer *input, *output;
	char* line;
	size_t n;
	input = bufferevent_get_input(bev);
	output = bufferevent_get_output(bev);

	line = evbuffer_readln(input, &n, EVBUFFER_EOL_CRLF);
	if (line) {
		for (unsigned int i = 0; i < n; ++i) {
			buffer += line[i];
		}

		// This is where you would send the buffer back to the server/game engine
		// for processing, but instead for now, we're just going to echo it to the console.


		if (buffer.compare("") != 0) {
			std::cout << "Socket " << socketfd << ": " << buffer << '\n';
			if (buffer.compare("quit") == 0) {
				error_cb(bev, BEV_EVENT_EOF);
			}
			else if (buffer.compare("shutdown") == 0) {
				buffer.clear();
				parent->Shutdown();
			}
			else {
				// Send the message to the buffer.
				Message* mess = new Message(buffer, socketfd, Message::inputMessage);
				parent->PutMessage(mess);
				buffer.clear();
			}
		}
	}
}

void TCPStream::write_cb(bufferevent *bev) {

}

void TCPStream::error_cb(bufferevent *bev, short error) {
	if (error & BEV_EVENT_EOF) {
		std::cout << "Connection closed." << '\n';
		delete this;
	}
}

const int TCPStream::GetSocket() {
	return socketfd;
}

const int TCPStream::Write(std::string outputMessage) {
	bufferevent_write(bEvent, outputMessage.c_str(), outputMessage.length() * sizeof(char));
	bufferevent_write(bEvent, "\n", 1);
	std::cout << "Sending message to " << socketfd << ": " << outputMessage << std::endl;
	return 0;
}
