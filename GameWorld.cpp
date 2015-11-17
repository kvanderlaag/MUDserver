#include "GameWorld.h"

#include <iostream>
#include <vector>

GameWorld::GameWorld() {
    std::cout << "Created a world..." << std::endl;
	players_ = new EntityList();
	rooms_ = new EntityList();

	Room *thera = new Room(rooms_->GetEntityCount(), "Thera", "South of Thera, Adventurers crowd the streets. Guards stand silent at the gates.");
	AddRoom(thera);

}

GameWorld::~GameWorld() {
    std::cout << "Destroyed a world..." << std::endl;
}

void GameWorld::AddRoom(Room *room) {
	std::cout << "adding room" << std::endl;
    rooms_->AddEntity(room);
}

void GameWorld::AddPlayer(Player *player) {
	players_->AddEntity( player );
}

void GameWorld::RemoveRoom(int id) {
    rooms_->RemoveEntity(id);
}

void GameWorld::RemovePlayer(int id) {
    players_->RemoveEntity(id);
}

GameEntity* GameWorld::GetRoom(int id) {
    return rooms_->GetEntity(id);
}

GameEntity* GameWorld::GetPlayer(int id) {
    return players_->GetEntity(id);
}

std::vector<Message*>* GameWorld::Look(int connection_id) {
	std::vector<Message*>* out = new std::vector<Message*>();

	/*// find player id
	int pid = current_players_->GetPlayerId(connection_id);
	// find player
	GameEntity player = *players_->GetEntity(pid);

	// find room id
	int rid = player->GetRoomId();
	// find room
	GameEntity room = *rooms_->GetEntity(rid);

	// get description
	std::string description = room->GetDescription();*/

	Message* msg = new Message("hi", connection_id, Message::outputMessage);
	out->push_back(msg);

	return out;
}

std::vector<Message*>* GameWorld::Look(int connection_id, std::string entity) {
	std::vector<Message*>* out = new std::vector<Message*>();

	/*// find player id
	int pid = current_players_->GetPlayerId(connection_id);
	// find player
	GameEntity player = *players_->GetEntity(pid);

	// find room id
	int rid = player->GetRoomId();
	// find room
	GameEntity room = *rooms_->GetEntity(rid);

	// find entity id 

	// find entity


	//get description*/


	Message* msg = new Message("hi", connection_id, Message::outputMessage);
	out->push_back(msg);

	return out;
}

std::vector<Message*>* GameWorld::Move(int connection_id, std::string exit) {
	std::vector<Message*>* out;



	Message* msg = new Message("hi", connection_id, Message::outputMessage);
	out->push_back(msg);

	return out;
}

std::vector<Message*>* GameWorld::Say(int connection_id, std::string words) {
	std::vector<Message*>* out = new std::vector<Message*>();



	Message* msg = new Message(words, connection_id, Message::outputMessage);
	out->push_back(msg);

	return out;
}

std::vector<Message*>* GameWorld::Take(int connection_id, std::string entity) {
	std::vector<Message*>* out = new std::vector<Message*>();



	Message* msg = new Message(entity, connection_id, Message::outputMessage);
	out->push_back(msg);

	return out;
}

std::vector<Message*>* GameWorld::Help(int connection_id) {
	std::vector<Message*>* out = new std::vector<Message*>();



	Message* msg = new Message("HELP", connection_id, Message::outputMessage);
	out->push_back(msg);

	return out;
}

std::vector<Message*>* GameWorld::SignUp(int connection_id, std::string login_name, std::string password) {
	std::vector<Message*> *out = new std::vector<Message*>();



	Message* msg = new Message("hi", connection_id, Message::outputMessage);
	out->push_back(msg);

	return out;
}

std::vector<Message*>* GameWorld::LogIn(int connection_id, std::string login_name, std::string password) {
	std::vector<Message*> *out = new std::vector<Message*>();



	Message* msg = new Message("hi", connection_id, Message::outputMessage);
	out->push_back(msg);

	return out;
}

std::vector<Message*>* GameWorld::LogOut(int connection_id) {
	std::vector<Message*> *out = new std::vector<Message*>();



	Message* msg = new Message("hi", connection_id, Message::outputMessage);
	out->push_back(msg);

	return out;
}
