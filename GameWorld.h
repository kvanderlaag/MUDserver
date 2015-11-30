#ifndef __GAMEWORLD_H__
#define __GAMEWORLD_H__

#include "EntityList.h"
#include "ConnectionList.h"
#include "Player.h"
#include "Room.h"
#include "Item.h"
#include "Message.h"
#include "Server.h"
#include "Utility.h"

#include <map>
#include <vector>
#include <sstream>
#include <cctype>
#include <memory>
#include <thread>

/**
* Header file for game world
*/

#define cDefault Utility::Color()
#define cBlue Utility::Color(4, 0, Utility::BOLD)
#define cRed Utility::Color(1, 0, Utility::BOLD)
#define cGreen Utility::Color(2, 0, Utility::BOLD)
#define cYellow Utility::Color(3, 0, Utility::BOLD)

class Server;

class GameWorld
{

private:
    EntityList* rooms_; // room_id/room_object
    EntityList* players_; // player_id/player_object

	// the master item list would be a good place for the Prototype design pattern.
	EntityList*  master_items_; // item_index/item_object

	EntityList* items_; // item_id/item_object
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

	std::unique_ptr<std::thread> updateThread;

	void ReceiveMessage(Message* message);

	void Look(int connection_id);
	void Look(int connection_id, std::string entity);
	void Move(int connection_id, std::string exit);
	void Say(int connection_id, std::string words);
	void Shout(int connection_id, std::string words);
	void Whisper(int connection_id, std::string name, std::string words);
	void Take(int connection_id, std::string entity);
	void DisplayInventory(int connection_id);
	void Drop(int connection_id, std::string entity);
	void Who(int connection_id);

	void LoadPlayers(std::string filename);
	void LoadItems(std::string filename);
	void LoadRooms(std::string filename);

	void Help(int connection_id);

	void SignUp(int connection_id, std::string login_name, std::string password);
	void LogIn(int connection_id, std::string login_name, std::string password);
	void LogOut(int connection_id);

	static void CreateUpdateThread(void* arg);
	void DoUpdate();
};

#endif // __GAMEWORLD_H__
