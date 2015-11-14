#include "Item.h"

Item::Item(int id, std::string description) : GameEntity(id, description) {
	std::cout <<"Created an item..." << std::endl;
}

Item::Item(int id, std::string name, std::string description) : GameEntity(id, name, description) {
	std::cout << "Created an item..." << std::endl;
}

Item::~Item() {
	std::cout << "Destroyed an item..." << std::endl;
}
