#include "TCPListener.h"
#include "TCPStream.h"

#include <iostream>

/**
 * Constructor. Initializes parent Server pointer,
 * Creates new event_base for libevent.
 */
TCPListener::TCPListener(Server* par, int port)
	: parent(par)
	, port(port)
	, base(event_base_new())
	, listenerfd(-1)
{
	if (!base) {
#ifdef _DEBUG_FLAG
		std::cout << "Error creating event base." << '\n';
#endif
	}
#ifdef _DEBUG_FLAG
	std::cout << "Creating new TCPListener on port " << port << ".\n";
#endif

}

/** Destructor. Frees the created libevent event base. */
TCPListener::~TCPListener()
{
	if (base) {
		std::cout << "Shutting down event base." << '\n';
		event_base_free(base);
	}
}

/** Shutdown. Kills parent server. */
void TCPListener::Shutdown() {
	parent->Shutdown();
}


/** Accept callback - passes libevent accept event to TCPListener instance. */
void TCPListener::do_accept(evutil_socket_t listener, short event, void* arg) {
	(static_cast<TCPListener*>(arg))->accept_cb(listener, event);
}

/**
 * Listen. Initializes socket for listener, binds it, and listens on the
 * specified port. Adds accept callback event to event base.
 */
void TCPListener::Listen() {
	sockaddr_in sin;
	if (!base) {
#ifdef _DEBUG_FLAG
		std::cout << "Cannot listen on port " << port << ". No event base created." << '\n';
#endif
		return;
	}

	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0;
	sin.sin_port = htons(port);
#ifdef _DEBUG_FLAG
	std::cout << "Creating socket." << "\n";
#endif
	listenerfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenerfd == -1) {
#ifdef _DEBUG_FLAG
		std::cout << "Error creating socket." << '\n';
#endif
		return;
	}
#ifdef _DEBUG_FLAG
	std::cout << "Created socket " << listenerfd << ".\n";

	std::cout << "Making socket non-blocking." << '\n';
#endif
	if (evutil_make_socket_nonblocking(listenerfd) == -1) {
#ifdef _DEBUG_FLAG
		std::cout << "Error making socket non-blocking." << '\n';
#endif
		ListenerClose();
		return;
	}

	if (bind(listenerfd, (sockaddr*)&sin, sizeof(sin)) < 0) {
#ifdef _DEBUG_FLAG
		std::cout << "Error binding socket." << '\n';
#endif
		ListenerClose();
		return;
	}

	if (listen(listenerfd, 10) < 0) {
#ifdef _DEBUG_FLAG
		std::cout << "Error listening on socket." << '\n';
#endif
		ListenerClose();
		return;
	}

#ifdef _DEBUG_FLAG
	std::cout << "Socket " << listenerfd << " listening on port " << port << ".\n";

	std::cout << "Creating new accept event." << '\n';
#endif
	listener_ev = event_new(base, listenerfd, EV_READ | EV_PERSIST, do_accept, (void*)this);
	if (!listener_ev) {
#ifdef _DEBUG_FLAG
		std::cout << "Error creating accept event." << '\n';
#endif
		ListenerClose();
	}

#ifdef _DEBUG_FLAG
	std::cout << "Adding accept event to event base." << '\n';
#endif
	if (event_add(listener_ev, NULL) == -1) {
#ifdef _DEBUG_FLAG
		std::cout << "Error adding accept event to event base." << '\n';
#endif
		ListenerClose();
	}

#ifdef _DEBUG_FLAG
	std::cout << "Starting event base." << '\n';
#endif
	if (event_base_dispatch(base) == -1) {
#ifdef _DEBUG_FLAG
		std::cout << "Error starting event base." << '\n';
#endif
		ListenerClose();
	}
}

/** ListenerClose. Utility function for closing sockets. */
void TCPListener::ListenerClose() {
#ifdef _WIN32
	closesocket(listenerfd);
#else
	close(listenerfd);
#endif
	return;
}

void TCPListener::ShutdownListener() {
	event_base_loopexit(base, NULL);
	ListenerClose();
}

/** GetParent. Returns the parent server object of the listener. */
Server& TCPListener::GetParent() {
	return *parent;
}

/** accept_cb. Callback function for accepting incoming connections. */
void TCPListener::accept_cb(evutil_socket_t listener, short event) {
	sockaddr_storage ss;
	socklen_t slen = sizeof(ss);

	int fd = accept(listener, (sockaddr*)&ss, &slen);

	if (fd < 0) {
#ifdef _DEBUG_FLAG
		std::cout << "Error accepting connection." << '\n';
#endif
	}
	else {
#ifdef _DEBUG_FLAG
		std::cout << "Accepted connection." << '\n';
#endif
		TCPStream* newStream = new TCPStream(this, fd);
		parent->AddConnection(newStream);
	}
}

/** PutMessage. Sends a message from a child stream to the parent server. */
void TCPListener::PutMessage(Message* mess) {
	parent->PutMessage(mess);
}

const event_base* TCPListener::GetBase() {
	return base;
}