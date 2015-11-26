#ifndef __ROOM_H__
#define __ROOM_H__

#include <iostream>
#include "EntityList.h"
#include "ConnectionList.h"
#include "GameEntity.h"

class Room : public GameEntity
{

private:
	EntityList* exits_;
	std::map<int, std::string> directions_;
	EntityList* items_;
	EntityList* players_;

public:
	Room(int id, std::string name);
	Room(int id, std::string name, std::string description);
	~Room(  );

	void AddItem(GameEntity* entity);
	void AddExit(GameEntity* entity);
	void AddPlayer(GameEntity* entity);
	void AddDirection(int id, std::string dir);

	void RemoveItem(int id);
	void RemoveExit(int id);
	void RemovePlayer(int id);

	GameEntity* GetExit(std::string exit);
	GameEntity* GetItem(int id);
	GameEntity* GetPlayer(int id);

	GameEntity* FindEntity(std::string name);
	
	std::vector<GameEntity*>* GetPlayerVector();
	std::map<int, std::string>* GetExitVector();
};

#endif // __ROOM_H__