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
		std::cout << "Duplicate id in connection list!!!" << std::endl;
	}

	map_.insert(std::pair<int, int>(connection_id, player_id));
}

/**
* From a connection ID, get the corresponding player ID
*/
int ConnectionList::GetPlayerId(int connection_id)
{
		std::map<int, int>::iterator it = map_.find(connection_id);
		if (it != map_.end()) {
			return map_.find(connection_id)->second;
		}
		
	return -1;
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

/**
* Return Connection vector for iteration
*/
std::vector<int>* ConnectionList::GetIdVector()
{
	std::vector<int>* id_vector = new std::vector<int>();

	if (!map_.empty())
	{
		typedef std::map<int, int>::iterator it_type;
		for (it_type iterator = map_.begin(); iterator != map_.end(); iterator++)
		{
			// iterator->first = key
			// iterator->second = value
			id_vector->push_back(iterator->second);
		}
	}
	return id_vector;
}