#pragma once

#include <map>
#include <vector>

/*
* Header file for ConnectionList
*/
class ConnectionList
{

private:
	std::map<int, int> map_;

public:
	ConnectionList();
	~ConnectionList();

	void AddConnection(const int connection_id, const int player_id);
	void RemoveConnection(const int connection_id);
	int GetPlayerId(const int connection_id);
	int GetConnectionCount();

	std::vector<int> GetIdVector();
};