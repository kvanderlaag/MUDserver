#include "ConnectionList.h"

#include <iostream>

ConnectionList::ConnectionList() {					/*Create a new connection list*/
	std::cout << "Created a connection list..." << std::endl;
}

ConnectionList::~ConnectionList() {					/*Remove a connection list*/
	std::cout << "Destroyed a connection list..." << std::endl;
}

void ConnectionList::AddConnection(int connection_id, int player_id) {	/*Add a connection to an existing connection list*/

	if (map_.find(connection_id) != map_.end()) {
		std::cout << "Duplicate id!!!" << std::endl;
	}

	map_.insert(std::pair<int, int>(connection_id, player_id));
}

int ConnectionList::GetPlayerId(int connection_id) {			/*From a connection ID, get the corresponding player ID*/
	if (!map_.empty()) {
		return map_.find(connection_id)->second;
	}
	return NULL;
}

void ConnectionList::RemoveConnection(int connection_id) {		/*Remove the connection ID from a list*/
	if (!map_.empty()) {
		if (map_.find(connection_id) != map_.end())
			map_.erase(connection_id);
		else
			std::cout << "Could not find the Connection to remove!!! ";
	}
}

int ConnectionList::GetConnectionCount() {				/*Returns the number of connections currently active*/
	return map_.size();
}
