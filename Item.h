/**Header file for item
 *item inherits GameEntity
*/
#ifndef __ITEM_H__
#define __ITEM_H__

#include <iostream>
#include "GameEntity.h"

class Item : public GameEntity {

private:

/** The public functions contain a default constructor
 * and a standard constructor that takes an ID, a name, and a description for the item,
 * and a destructor
*/
public:
	Item(int id, std::string description);
	Item(int id, std::string name, std::string description);
	~Item();
	
};

#endif	// __ITEM_H__ 

