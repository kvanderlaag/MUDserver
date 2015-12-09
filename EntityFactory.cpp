#include "EntityFactory.h"

EntityFactory::EntityFactory(GameWorld * world) :
	parent_(world)
{
	/*prototypes.push_back(new GameEntity(-1, "", parent_));
	prototypes["room"] = new Room(-1, "", parent_);
	prototypes["player"] = new Player(-1, "", parent_);
	prototypes["item"] = new Item(-1, "", parent_, -1);
	prototypes["npc"] = new NPC(-1, "", parent_, -1);*/
}

EntityFactory::~EntityFactory()
{
}

GameEntity * EntityFactory::MakeEntity(int type)
{
	//return prototypes[type]->clone();
	return nullptr;
}
