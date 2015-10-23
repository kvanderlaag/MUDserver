#include "Room.hpp"


Room::Room(int id, std::string description) : GameEntity(id, description) {
	std::cout << "Created a room..." << std::endl;
}

Room::~Room(  ) {
	std::cout << "Destroyed a room..." << std::endl;
}

void Room::AddExit(GameEntity *roomexit) {
	exits_->AddEntity(roomexit);	
}

void Room::AddItem(GameEntity *item) {
	items_->AddEntity(item);
}

GameEntity* Room::GetExit(int id) {
	return exits_->GetEntity(id);
}

GameEntity* Room::GetItem(int id) {
	return items_->GetEntity(id);
}
