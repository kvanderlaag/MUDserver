#include "ConnectionList.h"

#include <iostream>

/**
* Create a new connection list
*/
ConnectionList::ConnectionList()
{
	std::cout << "Created a connection list..." << std::endl;
}

/**
* Destroy a connection list
*/
ConnectionList::~ConnectionList()
{
	std::cout << "Destroyed a connection list..." << std::endl;
}

/**
* Add a connection to an existing connection list
*/
void ConnectionList::AddConnection(int connection_id, int player_id)
{

	if (map_.find(connection_id) != map_.end())
	{
		std::cout << "Duplicate id!!!" << std::endl;
	}

	map_.insert(std::pair<int, int>(connection_id, player_id));
}

/**
* From a connection ID, get the corresponding player ID
*/
int ConnectionList::GetPlayerId(int connection_id)
{
	if (!map_.empty())
	{
		return map_.find(connection_id)->second;
	}
	return NULL;
}

/**
* Remove the connection ID and corresponding player ID from a list
*/
void ConnectionList::RemoveConnection(int connection_id)
{
	if (!map_.empty())
	{
		if (map_.find(connection_id) != map_.end())
			map_.erase(connection_id);
		else
			std::cout << "Could not find the Connection to remove!!! ";
	}
}

/**
* Returns the number of connections currently active
*/
int ConnectionList::GetConnectionCount()
{
	return map_.size();
}
