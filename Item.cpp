#include "Item.hpp"

Item::Item(int id, std::string description) : GameEntity(id, description) {
	std::cout <<"Created an item..." << std::endl;
}

Item::~Item(  ) {
	std::cout << "Destroyed an item..." << std::endl;
}

void Item::PrintItem(int id, std::string description){
	std::cout << id << " " << description << std::endl;
} 

