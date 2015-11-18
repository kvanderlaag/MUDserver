/** Item.cpp implements the header file Item.h*/
#include "Item.h"

/**Create an item with ID and a description*/
Item::Item(int id, std::string description) : GameEntity(id, description)
{
	std::cout <<"Created an item..." << std::endl;
}

/**Create an item with an ID, a name and description*/
Item::Item(int id, std::string name, std::string description) : GameEntity(id, name, description)
{
	std::cout << "Created an item..." << std::endl;
}

/**A destructor that destorys an item*/
Item::~Item()
{
	std::cout << "Destroyed an item..." << std::endl;
}
