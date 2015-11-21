#include "GameWorld.h"

#include <iostream>
#include <vector>

/**
* Create a game world, with entity lists for players and rooms
*/
GameWorld::GameWorld(Server* par) :
	parent(par),
	players_(new EntityList()),
	rooms_(new EntityList())

{
    std::cout << "Created a world..." << std::endl;
	

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
* Find the player object given the connection id
*/
Player* GameWorld::FindPlayer(int connection_id)
{
	// find player id
	int pid = current_players_->GetPlayerId(connection_id);
	// find player
	GameEntity* pentity = players_->GetEntity(pid);
	Player* player = dynamic_cast<Player*>(pentity);

	return player;
}

/**
* Get the room object given the player object
*/
Room* GameWorld::FindRoom(Player* player)
{
	// find room id
	int rid = player->GetRoomId();
	// find room
	GameEntity* rentity = rooms_->GetEntity(rid);
	Room* room = dynamic_cast<Room*>(rentity);

	return room;
}

/**
* Player command
* Default look command with no given entity
* Returns the description of the room the player is standing in
*/
void GameWorld::Look(int connection_id)
{
	// find player
	Player* player = FindPlayer(connection_id);

	// find room
	Room* room = FindRoom(player);

	// find description
	std::string description = room->GetDescription();

	// create message
	Message* msg = new Message(description, connection_id, Message::outputMessage);
	
	//TODO place message on message buffer
	
}

/**
* Player command
* Look command with a given entity
* Returns the description of the entity
*/
void GameWorld::Look(int connection_id, std::string entity_name)
{
	// find player
	Player* player = FindPlayer(connection_id);

	// find room
	Room* room = FindRoom(player);

	// find entity
	GameEntity* entity = room->FindEntity(entity_name);

	// get description
	std::string description = entity->GetDescription();

	// create message
	Message* msg = new Message(description, connection_id, Message::outputMessage);
	
	//TODO place msg on message buffer

}

/**
* Player command
* Move command with a given exit
* Moves the player to the room that the exit is linked to
*/
void GameWorld::Move(int connection_id, std::string exit)
{
	// find player
	Player* player = FindPlayer(connection_id);

	// find room player is currently in
	Room* current_room = FindRoom(player);

	// remove player from current room list
	current_room->RemovePlayer(player->GetId);

	// find room player wants
	GameEntity* dest_rentity = current_room->GetExit();
	Room* dest_room = dynamic_cast<Room*>(dest_rentity);
	
	// add player to destination room list
	dest_room->AddPlayer(player);

	// send room description to player
	std::string description = dest_room->GetDescription();
	Message* msg = new Message(description, connection_id, Message::outputMessage);

	// send exit  to other players in room
	/*std::string entance = player->GetName() + " travelled to " + exit + ".";
	for (int i = 0; i < dest_room->, i++)
	{
		Message* omsg = new Message(entance, connection_id, Message::outputMessage);
	}

	// send player entrance to other players in room
	std::string entance = player->GetName() + " entered the area.";
	for (int i = 0; i< dest_room)
	Message* omsg = new Message(entance, connection_id, Message::outputMessage);*/

}

/**
* Player command
* Say command with a given message
* Forwards this message to all other players that are in the same room
*/
void GameWorld::Say(int connection_id, std::string words)
{
	// find player
	Player* player = FindPlayer(connection_id);

	// find room
	Room* room = FindRoom(player);

	// send player those words
	Message* msg = new Message(player->GetName + " said " + words, connection_id, Message::outputMessage);
}

/**
* Player command
* Shout command with a given string
* Forwards this message to all other players that are in the same world
*/
void GameWorld::Shout(int connection_id, std::string words)
{
	// find player
	Player* player = FindPlayer(connection_id);

	// send player those words
	Message* msg = new Message(player->GetName + " shouted " + words, connection_id, Message::outputMessage);
}

/**
* Player command
* Whisper command with a given string and player name
* Forwards this message to all other players that are in the same world
*/
void GameWorld::Whisper(int connection_id, std::string player_name, std::string words)
{
	// find player
	Player* player = FindPlayer(connection_id);

	// find room
	Room* room = FindRoom(player);

	// find other player
	GameEntity* other_pentity = room->FindEntity(player_name);

	// try to cast to item type
	Player* other_player = dynamic_cast<Player*>(other_pentity);

	// send player those words
	Message* msg = new Message(player->GetName + " whispered " + words, other_player->GetConnectionId, Message::outputMessage);
}

/**
* Player command
* Take command with a given entity
* Removes the entity from the room and adds it to the players inventory
*/
void GameWorld::Take(int connection_id, std::string entity)
{
	// find player
	Player* player = FindPlayer(connection_id);

	// find room
	Room* room = FindRoom(player);

	// find item
	GameEntity* ientity = room->FindEntity(entity);

	// try to cast to item type
	Item* item = dynamic_cast<Item*>(ientity);

	// add item to player item list
	player->AddItem(item);

	Message* msg = new Message(entity + " was added to your inventory", connection_id, Message::outputMessage);
}

/**
* Player command
* Help command
* Returns a list of commands for the player
*/
void GameWorld::Help(int connection_id)
{
	Message* msg = new Message("Help is on it's way!", connection_id, Message::outputMessage);
}

/**
* Player command
* Signup command
* Registers login name with password in the player list in game world
*/
void GameWorld::SignUp(int connection_id, std::string login_name, std::string password)
{
	// construct player
	Player* player = new Player(players_->GetEntityCount, login_name, password);
	player->SetRoomId(0);

	// add to player list
	players_->AddEntity(player);

	// message player
	Message* msg = new Message("You created new life. Please login.", connection_id, Message::outputMessage);
}

/**
* Player command
* Login command
* Checks if the given login name and password match an entry in the player list in game world
* Signs that player in if it matches
* Adds player to the connection list
*/
void GameWorld::LogIn(int connection_id, std::string login_name, std::string password)
{
	// find player
	GameEntity* pentity = players_->FindEntity(login_name);
	if (pentity == NULL)
	{
		Message* msg = new Message("Wrong username/password!", connection_id, Message::outputMessage);
		return;
	}

	Player* player = dynamic_cast<Player*>(pentity);

	// check password
	if (player->GetPassword != password)
	{
		Message* msg = new Message("Wrong username/password!", connection_id, Message::outputMessage);
		return;
	}

	// place into current players list
	current_players_->AddConnection(connection_id, player->GetId);

	// get player room, place into room player list
	Room* room = FindRoom(player);
	room->AddPlayer(player);

	// TODO message all players in room
	Message* msg = new Message(player->GetName + " phased into reality.", connection_id, Message::outputMessage);

	// name and password are correct
	Message* msg = new Message("You phased into reality", connection_id, Message::outputMessage);
}

/**
* Player command
* Logout command
* Cleans up the players variables and logs the player out of the game world
* Removes player from the connection list
*/
void GameWorld::LogOut(int connection_id)
{
	// remove player from connection list
	current_players_->RemoveConnection(connection_id);

	Player* player = FindPlayer(connection_id);

	// remove player from room list
	Room* room = FindRoom(player);
	room->RemovePlayer(player->GetId);

	Message* msg = new Message(player->GetName + " returned to the dream.", connection_id, Message::outputMessage);

	Message* msg = new Message("You returned to the dream", connection_id, Message::outputMessage);
}
