#include "Item.h"

Item::Item(int id, std::string description) : GameEntity(id, description) {				/*Create an item with a description*/
	std::cout <<"Created an item..." << std::endl;
}

Item::Item(int id, std::string name, std::string description) : GameEntity(id, name, description) {	/*Create an item with a name and description*/
	std::cout << "Created an item..." << std::endl;
}

Item::~Item() {												/*Destroy an item*/
	std::cout << "Destroyed an item..." << std::endl;
}
