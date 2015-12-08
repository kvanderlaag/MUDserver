#pragma once

#include "GameWorld.h"
#include "EntityList.h"
#include "Parser.h"

#include <concurrent_vector.h>

class GameWorld;
class Entityist;
class Parser;

class Memento
{
private:
	GameWorld & parent_;
	EntityList players_state_;
public:
	Memento(GameWorld & world);
	~Memento();

	EntityList & GetState();
	void SetState(EntityList & players);
};
