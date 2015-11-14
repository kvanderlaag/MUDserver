#ifndef __ITEM_H__
#define __ITEM_H__

#include <iostream>
#include "GameEntity.h"

class Item : public GameEntity {

private:

public:
	Item(int id, std::string description);
	Item(int id, std::string name, std::string description);
	~Item();
	
};

#endif	// __ITEM_H__ 

