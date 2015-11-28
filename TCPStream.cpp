#include "TCPStream.h"
#include "Message.h"

#include <iostream>



TCPStream::TCPStream(TCPListener* par, int socket)
	: parent(par)
	, socketfd(socket)
	, bEvent(bufferevent_socket_new((event_base*)par->GetBase(), socket, BEV_OPT_CLOSE_ON_FREE))
	, mIdentified(false)
{
	evutil_make_socket_nonblocking(socketfd);
	// Pop the telnet protocol crap from the socket.
	// TODO: Implement the telnet crap.
	// recv(socketfd, NULL, MAX_LINE, 0);
#ifdef _DEBUG_FLAG
	std::cout << "Socket " << socketfd << " is nonblocking." << '\n';

	std::cout << "Made new buffer event." << '\n';
#endif
	bufferevent_setcb(bEvent, do_read, do_write, do_error, (void*)this);
#ifdef _DEBUG_FLAG
	std::cout << "Set read callback and error callback." << '\n';
#endif
	bufferevent_setwatermark(bEvent, EV_READ | EV_WRITE, 0, MAX_LINE);
#ifdef _DEBUG_FLAG
	std::cout << "Set watermark." << '\n';
#endif
	bufferevent_enable(bEvent, EV_READ | EV_WRITE);
#ifdef _DEBUG_FLAG
	std::cout << "Enabled buffer event." << '\n';
#endif	
	bufferevent_read(bEvent, NULL, -1);
	
}


TCPStream::~TCPStream()
{
	bufferevent_free(bEvent);
#ifdef _DEBUG_FLAG
	std::cout << "Closing socket " << socketfd << '\n';
	std::cout << "Removed socket " << socketfd << " from connection list." << '\n';
#endif
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
	evbuffer *input;
	char* line;
	size_t n;
	input = bufferevent_get_input(bev);
	//output = bufferevent_get_output(bev);

	line = evbuffer_readln(input, &n, EVBUFFER_EOL_CRLF);
	if (line) {
		for (unsigned int i = 0; i < n; ++i) {
			buffer += line[i];
		}

		// This is where you would send the buffer back to the server/game engine
		// for processing, but instead for now, we're just going to echo it to the console.


		if (buffer.compare("") != 0) {
			// If the client has not yet been identified, strip non-alphanumeric characters from the buffer.
			if (!mIdentified) {
				std::string copy = buffer;
				buffer = "";
				for (std::string::iterator it = copy.begin(); it != copy.end(); it++) {
					if ((*it >= 'a' && *it <= 'z') || (*it >= '1' && *it >= '0') || (*it >= 'A' && *it <= 'Z') || (*it == ' ') || (*it == '_')) {
						buffer += *it;
					}
				}
				// Mark the client as identified.
				mIdentified = true;
			}
#ifdef _DEBUG_FLAG
			std::cout << "Socket " << socketfd << ": " << buffer << '\n';
#endif
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
	//std::cout << "Buffer write callback." << std::endl;
	
}

void TCPStream::error_cb(bufferevent *bev, short error) {
	if (error & BEV_EVENT_EOF) {
#ifdef _DEBUG_FLAG
		std::cout << "Connection closed." << '\n';
#endif
		parent->GetParent().RemoveConnection(this);
	}
}

const int TCPStream::GetSocket() {
	return socketfd;
}

const int TCPStream::Write(std::string outputMessage) {
	outputMessage += "\n\r> ";
	//bufferevent_write(bEvent, outputMessage.c_str(), outputMessage.length() * sizeof(char));
	send(socketfd, outputMessage.c_str(), outputMessage.length() * sizeof(char), 0);
#ifdef _DEBUG_FLAG	
	std::cout << "Sending message to " << socketfd << ": " << /*outputMessage <<*/ std::endl;
#endif
	return 0;
}
