#pragma once
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
#include "FileParser.h"

#include <map>
#include <vector>
#include <sstream>
#include <cctype>
#include <memory>
#include <thread>
#include <atomic>

/**
* Header file for game world
*/

class Player;
class Room;
class Item;
class Server;

class GameWorld
{

private:
    std::unique_ptr<EntityList> rooms_; // room_id/room_object
    std::unique_ptr<EntityList> players_; // player_id/player_object

	// the master item list would be a good place for the Prototype design pattern.
	std::unique_ptr<EntityList>  master_items_; // item_index/item_object

	std::unique_ptr<EntityList> items_; // item_id/item_object
	std::unique_ptr<ConnectionList> current_players_; // connection_id/player_id
	Server& parent;

	std::unique_ptr<std::thread> updateThread;
	std::unique_ptr<std::thread> saveThread;

public:
    GameWorld(Server& par);
    ~GameWorld();

    void AddRoom(Room& entity);
    void AddPlayer(Player& entity);

    void RemoveRoom(int id);
    void RemovePlayer(int id);

	GameEntity* GetRoom(int id);
    GameEntity* GetPlayer(int id);

	Player* FindPlayer(int connection_id);
	Room* FindPlayerRoom(Player& player);

	void ReceiveMessage(Message* message);

	void Look(int connection_id);
	void Look(int connection_id, std::string entity);
	void Move(int connection_id, std::string exit);
	void Say(int connection_id, std::string words);
	void Shout(int connection_id, std::string words);
	void Stats(int connection_id);
	void Whisper(int connection_id, std::string name, std::string words);
	void Take(int connection_id, std::string entity);
	void DisplayInventory(int connection_id);
	void Drop(int connection_id, std::string entity);
	void Who(int connection_id);
	void Description(int connection_id, std::string words);
	void Tell(int connection_id, std::string name, std::string words);
	void Password(int connection_id, std::string words);

	void LoadPlayers(std::string filename);
	void LoadItems(std::string filename);
	void LoadRooms(std::string filename);

	void Help(int connection_id);

	void SignUp(int connection_id, std::string login_name, std::string password);
	void LogIn(int connection_id, std::string login_name, std::string password);
	void LogOut(int connection_id);

	void StartUpdate();
	static void CreateSaveThread(void* arg);
	static void CreateUpdateThread(void* arg);
	void DoUpdate();
	void DoSave();

	void ReleaseThreads();

	Server& GetParent() const;
	EntityList& GetMasterItems() const;
	EntityList& GetItems() const;
};

#endif // __GAMEWORLD_H__
