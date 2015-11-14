#include "GameWorld.h"

#include <iostream>
#include <vector>

GameWorld::GameWorld(  ) {
    std::cout << "Created a world..." << std::endl;
	players_ = new EntityList();
	rooms_ = new EntityList();

	Room *thera = new Room(rooms_->GetEntityCount(), "Thera", "South of Thera, Adventurers crowd the streets. Guards stand silent at the gates.");
	AddRoom( thera );
	
}

GameWorld::~GameWorld(  ) {
    std::cout << "Destroyed a world..." << std::endl;
}

void GameWorld::AddRoom( Room *room ) {
	std::cout << "adding room" << std::endl;
    rooms_->AddEntity( room );
}

void GameWorld::AddPlayer( Player *player ) {
	players_->AddEntity( player );
}

void GameWorld::RemoveRoom( int id ) {
    rooms_->RemoveEntity( id );
}

void GameWorld::RemovePlayer( int id ) {
    players_->RemoveEntity( id );
}

GameEntity* GameWorld::GetRoom( int id ) {
    return rooms_->GetEntity( id );
}

GameEntity* GameWorld::GetPlayer( int id ) {
    return players_->GetEntity( id );
}

Message* GameWorld::SignUp(int connection_id, std::string login_name, std::string password) {
	Message msg = Message("hi", connection_id, Message::outputMessage);
	std::vector<Message> out;
	out.push_back(msg);

	return &out; 
}

