#ifndef __GAMEWORLD_H__
#define __GAMEWORLD_H__

#include "EntityList.h"
#include "ConnectionList.h"
#include "Player.h"
#include "Room.h"
#include "Item.h"
#include "Message.h"
#include "Server.h"

#include <map>
#include <vector>

/**
* Header file for game world
*/

class Server;

class GameWorld
{

private:
    EntityList* rooms_; // room_id/room_object
    EntityList* players_; // player_id/player_object
	ConnectionList* current_players_; // connection_id/player_id
	Server* parent;
	
public:
    GameWorld(Server* par);
    ~GameWorld();

    void AddRoom(Room* entity);
    void AddPlayer(Player* entity);

    void RemoveRoom(int id);
    void RemovePlayer(int id);

	GameEntity* GetRoom(int id);
    GameEntity* GetPlayer(int id);

	Player* FindPlayer(int connection_id);
	Room* FindPlayerRoom(Player* player);

	void Look(int connection_id);
	void Look(int connection_id, std::string entity);
	void Move(int connection_id, std::string exit);
	void Say(int connection_id, std::string words);
	void Shout(int connection_id, std::string words);
	void Whisper(int connection_id, std::string name, std::string words);
	void Take(int connection_id, std::string entity);

	void Help(int connection_id);

	void SignUp(int connection_id, std::string login_name, std::string password);
	void LogIn(int connection_id, std::string login_name, std::string password);
	void LogOut(int connection_id);
};

#endif // __GAMEWORLD_H__
