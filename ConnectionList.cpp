#include "ConnectionList.h"

#include <iostream>

ConnectionList::ConnectionList() {
	std::cout << "Created a connection list..." << std::endl;
}

ConnectionList::~ConnectionList() {
	std::cout << "Destroyed a connection list..." << std::endl;
}

void ConnectionList::AddConnection( int connection_id, int player_id ) {

	if (map_.find(connection_id) != map_.end()) {
		std::cout << "Duplicate id!!!" << std::endl;
	}

	map_.insert(std::pair<int, int>(connection_id, player_id));
}

int ConnectionList::GetPlayerId( int connection_id ) {
	if (!map_.empty()) {
		return map_.find(connection_id)->second;
	}
	return NULL;
}

void ConnectionList::RemoveConnection( int connection_id ) {
	if (!map_.empty()) {
		if (map_.find(connection_id) != map_.end())
			map_.erase(connection_id);
		else
			std::cout << "Could not find the Connection to remove!!! ";
	}
}

int ConnectionList::GetConnectionCount() {
	return map_.size();
}
