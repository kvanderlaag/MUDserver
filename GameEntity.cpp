/**GameEntity.cpp implements the header file GameEntity.h*/
#include "GameEntity.h"

#include <iostream>

/**Default constructor that creates a game entity by setting a permanent ID, name, and a blank description. */
GameEntity::GameEntity(int id, std::string name, GameWorld* world) :
	id_(id),
	name_(name),
	description_(""),
	world_(*world)
{

	//std::cout << "Created an entity..." << std::endl;
}

/**A standard constructor that creates a game entity with a description*/
GameEntity::GameEntity(int id, std::string name, std::string description, GameWorld* world) :
	id_(id),
	name_(name),
	description_(description),
	world_(*world)
{
  
	//std::cout << "Created an entity..." << std::endl;
}

/**A destructor that removes an entity*/
GameEntity::~GameEntity()
{
	std::cout << "Destroying entity " << GetName() << std::endl;
}

/**Get the Id of an entity*/
int GameEntity::GetId() const
{
	return id_;
}

/**Get the name of an entity*/
std::string GameEntity::GetName() const
{
	return name_;
}

/**Get the description of an entity*/
std::string GameEntity::GetDescription() const
{
	return description_;
}

/**Set the Id of an entity*/
void GameEntity::SetId(int id)
{
	id_ = id;
}

/**Set the name of an entity*/
void GameEntity::SetName(std::string name)
{
	name_ = name;
}

/**Change or set the description of an entity*/
void GameEntity::SetDescription(std::string description)
{
	description_ = description;
}

/**Print the ID, name, and description of an entity*/
void GameEntity::Print()
{
#ifdef _DEBUG_FLAG
	std::cout << id_ << " " << name_ << " " << description_ << std::endl;
#endif
}

GameWorld& GameEntity::GetWorld() const {
	return world_;
}
