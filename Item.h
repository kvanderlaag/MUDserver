/**Header file for item
 *item inherits GameEntity
*/
#ifndef __ITEM_H__
#define __ITEM_H__

#include "GameEntity.h"

#include <iostream>
#include <vector>


class Item : public GameEntity
{

private:
	std::vector<std::string> mShortNames;

/** The public functions contain a default constructor
 * and a standard constructor that takes an ID, a name, and a description for the item,
 * and a destructor
*/
public:
	Item(int id, std::string description);
	Item(int id, std::string name, std::string description);
	Item(int newId, const Item& other);
	void AddShortName(std::string name);
	std::vector<std::string> GetShortNameVector() const;
	bool FindShortName(std::string shortName) const;
	
	~Item();
};

#endif	// __ITEM_H__ 

