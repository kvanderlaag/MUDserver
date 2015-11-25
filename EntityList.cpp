/**
* EntityList.cpp implements the header file EntityList.h
*/
#include "EntityList.h"

#include <iostream>

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
    //std::cout << "Destroyed a list..." << std::endl;
}

/**
* Takes the pointer of a game entity and adds the game entity to an existing list.
* It returns warning if the passed IDs are duplicated.
*/
void EntityList::AddEntity(GameEntity* game_entity)
{			
	if(map_.find(game_entity->GetId()) != map_.end())
	{
        std::cout << "Duplicate id in entity list!!!" << std::endl;
		return;
    }
	
    map_.insert(std::pair<int,GameEntity*>(game_entity->GetId(), game_entity));
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
        return map_.find(id)->second;
    }
    return NULL;
}

/**
* Get the entity corresponding to an String
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
			if (iterator->second->GetName() == name)
			{
				return iterator->second;
			}
		}
	}
	return NULL;
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
std::vector<GameEntity*>* EntityList::GetEntityVector()
{
	std::vector<GameEntity*>* entity_vector = new std::vector<GameEntity*>();

	if (!map_.empty())
	{
		typedef std::map<int, GameEntity*>::iterator it_type;
		for (it_type iterator = map_.begin(); iterator != map_.end(); iterator++)
		{
			// iterator->first = key
			// iterator->second = value
			entity_vector->push_back(iterator->second);
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