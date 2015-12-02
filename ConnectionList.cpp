#include "ConnectionList.h"

#include <iostream>

/**
* Create a new connection list
*/
ConnectionList::ConnectionList()
{
#ifdef _DEBUG_FLAG
	std::cout << "Created a connection list..." << std::endl;
#endif
}

/**
* Destroy a connection list
*/
ConnectionList::~ConnectionList()
{
#ifdef _DEBUG_FLAG
	std::cout << "Destroyed a connection list..." << std::endl;
#endif
}

/**
* Add a connection to an existing connection list
*/
void ConnectionList::AddConnection(const int connection_id, const int player_id)
{

	if (map_.find(connection_id) != map_.end())
	{
#ifdef _DEBUG_FLAG
		std::cout << "Duplicate id in connection list!!!" << std::endl;
#endif
	}

	map_.insert(std::pair<int, int>(connection_id, player_id));
}

/**
* From a connection ID, get the corresponding player ID
*/
int ConnectionList::GetPlayerId(const int connection_id)
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
void ConnectionList::RemoveConnection(const int connection_id)
{
	if (!map_.empty())
	{
		if (map_.find(connection_id) != map_.end())
			map_.erase(connection_id);
#ifdef _DEBUG_FLAG
		else
			std::cout << "Could not find the Connection to remove!!! ";
#endif
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
std::vector<int> ConnectionList::GetIdVector()
{
	std::vector<int> id_vector = std::vector<int>();

	if (!map_.empty())
	{
		typedef std::map<int, int>::iterator it_type;
		for (it_type iterator = map_.begin(); iterator != map_.end(); iterator++)
		{
			// iterator->first = key
			// iterator->second = value
			id_vector.push_back(iterator->second);
		}
	}
	return id_vector;
}