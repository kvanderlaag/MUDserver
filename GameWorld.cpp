#include "GameWorld.h"

#include <iostream>
#include <vector>

/**
* Create a game world, with entity lists for players and rooms
*/
GameWorld::GameWorld()
{
    std::cout << "Created a world..." << std::endl;
	players_ = new EntityList();
	rooms_ = new EntityList();
	

	Room *thera = new Room(rooms_->GetEntityCount(), "Thera", "South of Thera. Adventurers crowd the streets. Guards stand silent at the gates.");
	AddRoom(thera);

}


/**
* Destroy a game world
*/
GameWorld::~GameWorld()
{
    std::cout << "Destroyed a world..." << std::endl;
}

/**
* Add a room to the room list in game world
*/
void GameWorld::AddRoom(Room *room)
{
	std::cout << "adding room" << std::endl;
    rooms_->AddEntity(room);
}

/**
* Add a player to the player list in game world
*/
void GameWorld::AddPlayer(Player *player)
{
	players_->AddEntity( player );
}

/**
* Remove a room from the room list in game world
*/
void GameWorld::RemoveRoom(int id)
{
    rooms_->RemoveEntity(id);
}

/**
* Remove a player from the player list in game world
*/
void GameWorld::RemovePlayer(int id)
{
    players_->RemoveEntity(id);
}

/**
* Get the room object given the room id
*/
GameEntity* GameWorld::GetRoom(int id)
{
    return rooms_->GetEntity(id);
}

/**
* Get the player object given the player id
*/
GameEntity* GameWorld::GetPlayer(int id)
{
    return players_->GetEntity(id);
}

/**
* Player command
* Default look command with no given entity
* Returns the description of the room the player is standing in
*/
std::vector<Message*>* GameWorld::Look(int connection_id)
{
	std::vector<Message*>* out = new std::vector<Message*>();

	/* find player id*/
	int pid = current_players_->GetPlayerId(connection_id);
	/*find player*/
	GameEntity* pentity = players_->GetEntity(pid); 
	Player* player = dynamic_cast<Player*>(pentity);

	// find room id
	int rid = player->GetRoomId();
	// find room
	GameEntity* rentity = rooms_->GetEntity(rid);
	Room* room = dynamic_cast<Room*>(rentity);

	/*get description*/
	std::string description = room->GetDescription();

	Message* msg = new Message(description, connection_id, Message::outputMessage);
	out->push_back(msg);

	return out;
}

/**
* Player command
* Look command with a given entity
* Returns the description of the entity
*/
std::vector<Message*>* GameWorld::Look(int connection_id, std::string entity_name)
{
	std::vector<Message*>* out = new std::vector<Message*>();

	/* find player id*/
	int pid = current_players_->GetPlayerId(connection_id);
	/*find player*/
	GameEntity* pentity = players_->GetEntity(pid);
	Player* player = dynamic_cast<Player*>(pentity);

	// find room id
	int rid = player->GetRoomId();
	// find room
	GameEntity* rentity = rooms_->GetEntity(rid);
	Room* room = dynamic_cast<Room*>(rentity);

	// find entity
	GameEntity* entity = room->FindEntity(entity_name);

	/*get description*/
	std::string description = entity->GetDescription();

	Message* msg = new Message(description, connection_id, Message::outputMessage);
	out->push_back(msg);

	return out;
}

/**
* Player command
* Move command with a given exit
* Moves the player to the room that the exit is linked to
*/
std::vector<Message*>* GameWorld::Move(int connection_id, std::string exit)
{
	std::vector<Message*>* out;



	Message* msg = new Message("hi", connection_id, Message::outputMessage);
	out->push_back(msg);

	return out;
}

/**
* Player command
* Say command with a given message
* Forwards this message to all other players that are in the same room
*/
std::vector<Message*>* GameWorld::Say(int connection_id, std::string words)
{
	std::vector<Message*>* out = new std::vector<Message*>();



	Message* msg = new Message(words, connection_id, Message::outputMessage);
	out->push_back(msg);

	return out;
}

/**
* Player command
* Take command with a given entity
* Removes the entity from the room and adds it to the players inventory
*/
std::vector<Message*>* GameWorld::Take(int connection_id, std::string entity)
{
	std::vector<Message*>* out = new std::vector<Message*>();



	Message* msg = new Message(entity, connection_id, Message::outputMessage);
	out->push_back(msg);

	return out;
}

/**
* Player command
* Help command
* Returns a list of commands for the player
*/
std::vector<Message*>* GameWorld::Help(int connection_id)
{
	std::vector<Message*>* out = new std::vector<Message*>();



	Message* msg = new Message("HELP", connection_id, Message::outputMessage);
	out->push_back(msg);

	return out;
}

/**
* Player command
* Signup command
* Registers login name with password in the player list in game world
*/
std::vector<Message*>* GameWorld::SignUp(int connection_id, std::string login_name, std::string password)
{
	std::vector<Message*> *out = new std::vector<Message*>();



	Message* msg = new Message("hi", connection_id, Message::outputMessage);
	out->push_back(msg);

	return out;
}

/**
* Player command
* Login command
* Checks if the given login name and password match an entry in the player list in game world
* Signs that player in if it matches
* Adds player to the connection list
*/
std::vector<Message*>* GameWorld::LogIn(int connection_id, std::string login_name, std::string password)
{
	std::vector<Message*> *out = new std::vector<Message*>();



	Message* msg = new Message("hi", connection_id, Message::outputMessage);
	out->push_back(msg);

	return out;
}

/**
* Player command
* Logout command
* Cleans up the players variables and logs the player out of the game world
* Removes player from the connection list
*/
std::vector<Message*>* GameWorld::LogOut(int connection_id)
{
	std::vector<Message*> *out = new std::vector<Message*>();



	Message* msg = new Message("hi", connection_id, Message::outputMessage);
	out->push_back(msg);

	return out;
}
