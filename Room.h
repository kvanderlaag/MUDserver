#pragma once
#ifndef __ROOM_H__
#define __ROOM_H__

#include <iostream>
#include "EntityList.h"
#include "ConnectionList.h"
#include "GameEntity.h"
#include "Item.h"
#include "Player.h"
#include "NPC.h"
#include <cctype>

class Room : public GameEntity
{

private:
	EntityList* exits_;
	std::map<int, std::string> directions_;
	EntityList* items_;
	std::vector<int> original_items_;
	EntityList* players_;
	std::unique_ptr<EntityList> mobs_;
	std::vector<int> original_mobs_;

public:

	Room(int id, std::string name, GameWorld* world);
	Room(int id, std::string name, std::string description, GameWorld* world);
	~Room(  );

	void AddItem(GameEntity& entity);
	void AddMasterItem(int id);
	void AddMasterMob(int id);
	void SpawnItem(int masterId);
	void SpawnMob(int masterId);
	void RespawnItems();
	void RespawnMobs();
	void AddExit(GameEntity& entity);
	void AddPlayer(GameEntity& entity);
	void AddDirection(int id, std::string dir);
	void AddMob(GameEntity& entity);

	void RemoveItem(int id);
	void RemoveExit(int id);
	void RemovePlayer(int id);
	void RemoveMob(int id);

	GameEntity* GetExit(std::string exit);
	GameEntity* GetItem(int id);
	GameEntity* GetPlayer(int id);
	GameEntity* GetMob(int id);

	GameEntity* FindEntity(std::string name) const;
	GameEntity* FindExit(std::string name) const;
	GameEntity* FindItem(std::string name) const;
	GameEntity* FindPlayer(std::string name) const;
	GameEntity* FindMob(std::string name) const;


	std::vector<GameEntity*> GetPlayerVector();
	std::map<int, std::string> GetExitVector();
	std::vector<GameEntity*> GetItemVector();
	std::vector<GameEntity*> GetMobVector();
};

#endif // __ROOM_H__
