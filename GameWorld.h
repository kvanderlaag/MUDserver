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
#include "NPC.h"
#include "BattleList.h"
#include "CharacterClassList.h"
#include "CharacterClass.h"
#include "Memento.h"

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
class BattleList;
class CharacterClassList;
class Memento;

class GameWorld
{

private:
	static bool running;
	std::unique_ptr<EntityList> rooms_; // room_id/room_object
	std::unique_ptr<EntityList> players_; // player_id/player_object
	std::unique_ptr<EntityList> items_; // item_id/item_object
	std::unique_ptr<EntityList> mobs_;

	// the master item list would be a good place for the Prototype design pattern.
	std::unique_ptr<EntityList> master_items_; // item_index/item_object
	std::unique_ptr<EntityList> master_mobs_;

	std::unique_ptr<BattleList> battles_;
	std::unique_ptr<CharacterClassList> character_classes_;

	std::unique_ptr<ConnectionList> current_players_; // connection_id/player_id
	Server& parent;

	std::unique_ptr<std::thread> updateThread;
	std::unique_ptr<std::thread> saveThread;
	std::unique_ptr<std::thread> battleUpdateThread;

	std::unique_ptr<Memento> memento;

public:
	GameWorld(Server& par);
	~GameWorld();

	void AddRoom(Room& entity);
	void AddPlayer(Player& entity);
	void AddMob(NPC& entity);

	void RemoveRoom(int id);
	void RemovePlayer(int id);
	void RemoveMob(NPC& entity);

	GameEntity* GetRoom(int id);
	GameEntity* GetPlayer(int id);

	Player* FindPlayer(int connection_id);
	Room* FindPlayerRoom(Player& player);
	
	NPC* FindMob(int mobId);
	Room* FindMobRoom(NPC& mob);
	

	void ReceiveMessage(Message* message);

	void Attack(int connection_id, std::string entity);
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

	void Help(int connection_id);

	void SignUp(int connection_id, std::string login_name, std::string password);
	void LogIn(int connection_id, std::string login_name, std::string password);
	void LogOut(int connection_id);

	void StartUpdate();
	static void CreateSaveThread(void* arg);
	static void CreateUpdateThread(void* arg);
	static void CreateBattleUpdateThread(void* arg);
	void DoUpdate();
	void DoSave();
	void DoBattleUpdate();

	void ReleaseThreads();

	Server& GetParent() const;
	EntityList& GetRooms() const;
	EntityList& GetPlayers() const;
	EntityList& GetItems() const;
	EntityList& GetMobs() const;

	EntityList& GetMasterItems() const;
	EntityList& GetMasterMobs() const;

	BattleList& GetBattles() const;
	CharacterClassList& GetCharacterClasses() const;
};

#endif // __GAMEWORLD_H__
