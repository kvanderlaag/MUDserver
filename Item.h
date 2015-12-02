#pragma once
/**Header file for item
 *item inherits GameEntity
*/
#ifndef __ITEM_H__
#define __ITEM_H__

#include "GameEntity.h"
#include "GameWorld.h"

#include <iostream>
#include <vector>

class GameWorld;

class Item : public GameEntity
{

private:
	std::vector<std::string> mShortNames;

/** The public functions contain a default constructor
 * and a standard constructor that takes an ID, a name, and a description for the item,
 * and a destructor
*/
public:
	Item(int id, std::string description, GameWorld* world);
	Item(int id, std::string name, std::string description, GameWorld* world);
	Item(int newId, const Item& other);
	void AddShortName(std::string name);
	std::vector<std::string> GetShortNameVector() const;
	bool FindShortName(std::string shortName) const;
	
	~Item();
};

#endif	// __ITEM_H__ 

