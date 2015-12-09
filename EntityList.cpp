/**
* EntityList.cpp implements the header file EntityList.h
*/
#include "EntityList.h"

#include <iostream>
#include <algorithm>

/**
* Default constructor that creates an entity list then prints out the information
*/
EntityList::EntityList()
{	
	next_ids_.push_back(0);
	//std::cout << "Created a list..." << std::endl;
}

/**
* Destructor that delete an entity list then prints out the information
*/
EntityList::~EntityList()
{	
	std::cout << "Destroying EntityList" << std::endl;
}

/**
* Takes the pointer of a game entity and adds the game entity to an existing list.
* It returns warning if the passed IDs are duplicated.
*/
void EntityList::AddEntity(GameEntity& game_entity)
{			
	if(map_.find(game_entity.GetId()) != map_.end())
	{
		std::cout << "Duplicate id in entity list!!!" << std::endl;
		return;
	}
	
	map_.insert(std::pair<int,GameEntity*>(game_entity.GetId(), &game_entity));
}

/**
* Remove an entity corresponding to an ID
*/
void EntityList::RemoveEntity(int id)
{
	if (!map_.empty())
	{
		if (map_.find(id) != map_.end())
		{
			map_.erase(id);
			next_ids_.push_back(id);
		}
		else
		{
			std::cout << "Could not find the GameEntity to remove!!! ";
		}
	}
}

/**
* Get the entity corresponding to an ID
*/
GameEntity* EntityList::GetEntity(int id)
{	
	if( !map_.empty() )
	{
		std::map<int, GameEntity*>::iterator it = map_.find(id);
		if (it != map_.end()) {
			return it->second;
		}
	}
	return nullptr;
}

/**
* Get the entity corresponding to a String
* Slow
*/
GameEntity* EntityList::FindEntity(std::string name)
{
	if (!map_.empty())
	{
		typedef std::map<int, GameEntity*>::iterator it_type;
		for (it_type iterator = map_.begin(); iterator != map_.end(); iterator++)
		{
			// iterator->first = key
			// iterator->second = value
			GameEntity& map_value = *(iterator->second);
			std::string map_value_name = map_value.GetName();

			std::transform(name.begin(), name.end(), name.begin(), ::tolower);
			std::transform(map_value_name.begin(), map_value_name.end(), map_value_name.begin(), ::tolower);

			if (map_value_name == name)
			{
				return iterator->second;
			}
		}
	}
	return nullptr;
}

/**
* Return how many entities are in the list
*/
int EntityList::GetEntityCount()
{	
	return map_.size();
}

/**
* Return Entity vector for iteration
*/
std::vector<GameEntity*> EntityList::GetEntityVector()
{
	std::vector<GameEntity*> entity_vector;

	if (!map_.empty())
	{
		typedef std::map<int, GameEntity*>::iterator it_type;
		for (it_type iterator = map_.begin(); iterator != map_.end(); iterator++)
		{
			// iterator->first = key
			// iterator->second = value
			entity_vector.push_back(iterator->second);
		}
	}
	return entity_vector;
}

/**
* Return next id available in the list
*/
int EntityList::GetNextId()
{
	int id = next_ids_.back();

	next_ids_.pop_back();

	// if its empty, push id+1 onto it
	if (next_ids_.size() == 0)
	{
		next_ids_.push_back(id + 1);
	}

	return id;
}

/**
* Make id available again
*/
void EntityList::PutNextId(int id)
{
	next_ids_.push_back(id);
}

void EntityList::Print()
{
	typedef std::map<int, GameEntity*>::iterator it_type;
	for (it_type iterator = map_.begin(); iterator != map_.end(); iterator++)
	{
		// iterator->first = key
		// iterator->second = value
		std::cout << iterator->first << " " << iterator->second->GetName() << std::endl;
	}
}