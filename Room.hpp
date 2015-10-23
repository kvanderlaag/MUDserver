#ifndef __ROOM_H__
#define __ROOM_H__

#include <iostream>
#include "EntityList.hpp"
#include "GameEntity.hpp"

class Room : public GameEntity {

private:
	EntityList* exits_;
	EntityList* items_;

public:
	Room(int id, std::string description);
	~Room(  );

	void AddItem(GameEntity* entity);
	void AddExit(GameEntity* entity);

	//Room *AddExit();
	GameEntity *GetExit(int id);
	//Room *AddItem();
	GameEntity *GetItem(int id);
};

#endif // __ROOM_H__