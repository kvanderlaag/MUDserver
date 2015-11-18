#ifndef __CONNECTIONLIST_H__
#define __CONNECTIONLIST_H__

#include <map>

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

	void AddConnection(int connection_id, int player_id);
	void RemoveConnection(int connection_id);
	int GetPlayerId(int connection_id);
	int GetConnectionCount();

};

#endif // __CONNECTIONLIST_H__
