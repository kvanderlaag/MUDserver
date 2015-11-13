#include "Room.h"


Room::Room(int id, std::string name) : GameEntity(id, name) {
	std::cout << "Created a room..." << std::endl;
}

Room::Room(int id, std::string name, std::string description) : GameEntity(id, name, description) {
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

void Room::AddPlayer(GameEntity *player) {
	players_->AddEntity(player);
}

void Room::RemoveExit(int id) {
    exits_->RemoveEntity(id);
}

void Room::RemoveItem(int id) {
	items_->RemoveEntity(id);
}

void Room::RemovePlayer(int id) {
	players_->RemoveEntity(id);
}

GameEntity* Room::GetExit(int id) {
	return exits_->GetEntity(id);
}

GameEntity* Room::GetItem(int id) {
	return items_->GetEntity(id);
}

GameEntity* Room::GetPlayer(int id) {
	return players_->GetEntity(id);
}


