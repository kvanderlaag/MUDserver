#include "TCPListener.h"
#include "TCPStream.h"

#include <iostream>

// Constructor. Initializes parent Server pointer,
// Creates new event_base for libevent.
TCPListener::TCPListener(Server* par, int port)
{
	parent = par;
	base = event_base_new();

	if (!base) {
		std::cout << "Error creating event base." << '\n';
	}

	this->port = port;


}

// Destructor. Frees the created libevent event base.
TCPListener::~TCPListener()
{
	if (base) {
		std::cout << "Shutting down event base." << '\n';
		event_base_free(base);
	}
}

// Shutdown. Kills parent server.
void TCPListener::Shutdown() {
	parent->Shutdown();
}

// Accept callback - passes libevent accept event to TCPListener instance.
void TCPListener::do_accept(evutil_socket_t listener, short event, void* arg) {
	(static_cast<TCPListener*>(arg))->accept_cb(listener, event);
}

// Listen. Initializes socket for listener, binds it, and listens on the
// specified port. Adds accept callback event to event base.
void TCPListener::Listen() {
	sockaddr_in sin;
	evutil_socket_t listener;
	event* listener_ev;
	if (!base) {
		std::cout << "Cannot listen on port " << port << ". No event base created." << '\n';
		return;
	}

	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0;
	sin.sin_port = htons(port);
	std::cout << "Creating socket" << ".\n";
	listener = socket(AF_INET, SOCK_STREAM, 0);
	if (listener == -1) {
		std::cout << "Error creating socket." << '\n';
		return;
	}

	std::cout << "Created socket " << listener << ".\n";

	std::cout << "Making socket non-blocking." << '\n';
	if (evutil_make_socket_nonblocking(listener) == -1) {
		std::cout << "Error making socket non-blocking." << '\n';
		ListenerClose(listener);
		return;
	}

	if (bind(listener, (sockaddr*)&sin, sizeof(sin)) < 0) {
		std::cout << "Error binding socket." << '\n';
		ListenerClose(listener);
		return;
	}

	if (listen(listener, 10) < 0) {
		std::cout << "Error listening on socket." << '\n';
		ListenerClose(listener);
		return;
	}

	std::cout << "Socket " << listener << " listening on port " << port << ".\n";

	std::cout << "Creating new accept event." << '\n';
	listener_ev = event_new(base, listener, EV_READ | EV_PERSIST, do_accept, (void*)this);
	if (!listener_ev) {
		std::cout << "Error creating accept event." << '\n';
		ListenerClose(listener);
	}

	std::cout << "Adding accept event to event base." << '\n';
	if (event_add(listener_ev, NULL) == -1) {
		std::cout << "Error adding accept event to event base." << '\n';
		ListenerClose(listener);
	}

	std::cout << "Starting event base." << '\n';
	if (event_base_dispatch(base) == -1) {
		std::cout << "Error starting event base." << '\n';
		ListenerClose(listener);
	}
}

// ListenerClose. Utility function for closing sockets.
void TCPListener::ListenerClose(const int socketfd) {
#ifdef _WIN32
	closesocket(socketfd);
#else
	close(listener);
#endif
	return;
}

// GetParent. Returns the parent server object of the listener.
Server* TCPListener::GetParent() {
	return parent;
}

// accept_cb. Callback function for accepting incoming connections.
void TCPListener::accept_cb(evutil_socket_t listener, short event) {
	sockaddr_storage ss;
	socklen_t slen = sizeof(ss);

	int fd = accept(listener, (sockaddr*)&ss, &slen);
	std::cout << "Accepted connection." << '\n';
	if (fd < 0) {
		perror("accept");
	}
	else {
		TCPStream* newStream = new TCPStream(this, fd);
		bufferevent* bev;
		evutil_make_socket_nonblocking(fd);
		std::cout << "Socket " << fd << " is nonblocking." << '\n';
		bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
		std::cout << "Made new buffer event." << '\n';
		bufferevent_setcb(bev, newStream->do_read, NULL, newStream->do_error, (void*)newStream);
		std::cout << "Set read callback and error callback." << '\n';
		bufferevent_setwatermark(bev, EV_READ, 0, MAX_LINE);
		std::cout << "Set watermark." << '\n';
		bufferevent_enable(bev, EV_READ | EV_WRITE);
		std::cout << "Enabled buffer event." << '\n';
		parent->AddConnection(newStream);
	}
}

// PutMessage. Sends a message from a child stream to the parent server.
void TCPListener::PutMessage(Message* mess) {
	parent->PutMessage(mess);
}