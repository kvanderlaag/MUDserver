#ifndef __ITEM_H__
#define __ITEM_H__

#include <iostream>
#include "GameEntity.h"

class Item : public GameEntity {

private:
	int id;

public:
	Item(int id, std::string description);
	~Item(  );

	void PrintItem(int id, std::string description);
	
};

#endif	// __ITEM_H__ 

