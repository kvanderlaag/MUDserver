#pragma once

#include "GameEntity.h"
#include "Room.h"
#include "Player.h"
#include "Item.h"
#include "NPC.h"

#include <vector>

class GameEntity;
class Room;
class Player;
class Item;
class NPC;

/*Header file for EntityList*/
class EntityFactory
{
private:
	GameWorld * parent_;
	static std::vector<GameEntity*> prototypes;

public:
	EntityFactory(GameWorld * world);
	~EntityFactory();
	static GameEntity* MakeEntity(int type);

};