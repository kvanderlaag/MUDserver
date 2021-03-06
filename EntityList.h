#pragma once
#ifndef __ENTITYLIST_H__
#define __ENTITYLIST_H__

#include "GameEntity.h"

#include <map>
#include <vector>

/*Header file for EntityList*/
class EntityList
{

/* Private variable uses a map to implement the list of entities */
protected:
	std::map<int, GameEntity*> map_;
	std::vector<int> next_ids_; // stack


/* Public functions have a default constructor for the class, a destructor
 * Other functions include AddEntity which takes a pointer of game entity and adds the entity to the list
 * RemoveEntity takes the ID of the entity and removes it from the list
 * GetEntity takes the ID of the entity and locates the item on the list
 * GetEntityCount returns the the current size of the list containing entities
*/
public:
	EntityList();
	~EntityList();

	virtual void AddEntity(GameEntity& game_entity);
	virtual void RemoveEntity(int id);
	virtual GameEntity* GetEntity(int id);
	virtual GameEntity* FindEntity(std::string name);

	int GetEntityCount();
	virtual std::vector<GameEntity*> GetEntityVector();

	int GetNextId();
	void PutNextId(int id);
	virtual void Print();

};

#endif // __ENTITYLIST_H__
