#ifndef __ROOM_H__
#define __ROOM_H__

#include <iostream>
#include "EntityList.hpp"
#include "GameEntity.hpp"

class Room : public GameEntity {

private:
	EntityList* exits_;
	EntityList* items_;
	EntityList* players_;

public:
	Room(int id, std::string description);
	~Room(  );

	void AddItem(GameEntity* entity);
	void AddExit(GameEntity* entity);
	void AddPlayer(GameEntity* entity);

	void RemoveItem(int id);
	void RemoveExit(int id);
	void RemovePlayer(int id);

	GameEntity *GetExit(int id);
	GameEntity *GetItem(int id);
	GameEntity *GetPlayer(int id);
};

#endif // __ROOM_H__