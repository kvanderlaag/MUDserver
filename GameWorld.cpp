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


	//Room *thera = new Room(rooms_->GetNextId(), "Thera", "South of Thera. Adventurers crowd the streets. Guards stand silent at the gates.");
	//AddRoom(thera);

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
	std::cout << "Added a room" << std::endl;
    rooms_->AddEntity(room);
}

/**
* Add a player to the player list in game world
*/
void GameWorld::AddPlayer(Player *player)
{
	players_->AddEntity(player);
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
Room* GameWorld::FindPlayerRoom(Player* player)
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
	Room* room = FindPlayerRoom(player);

	// find description
	std::string description = room->GetDescription();

	// create message
	Message* msg = new Message(description, connection_id, Message::outputMessage);

	// place message on message buffer
	parent->PutMessage(msg);

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
	Room* room = FindPlayerRoom(player);

	// find entity
	GameEntity* entity = room->FindEntity(entity_name);

	// get description
	std::string description = entity->GetDescription();

	// create message
	Message* msg = new Message(description, connection_id, Message::outputMessage);

	// place msg on message buffer
	parent->PutMessage(msg);

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
	Room* current_room = FindPlayerRoom(player);

	// find room player wants
	GameEntity* dest_rentity = current_room->GetExit(exit);
	Room* dest_room = dynamic_cast<Room*>(dest_rentity);


	// remove player from current room list
	current_room->RemovePlayer(player->GetId());

	// send exit to other players in room
	std::vector<GameEntity*>* current_room_players = current_room->GetPlayerVector();
	for (int i = 0; i < current_room_players->size(); i++)
	{
		Player* room_player = dynamic_cast<Player*>(current_room_players->at(i));
		Message* exit_msg = new Message(player->GetName() + " headed towards " + dest_room->GetName() + ".", room_player->GetConnectionId(), Message::outputMessage);
		parent->PutMessage(exit_msg);
	}


	// send entrance to other players in new room
	std::vector<GameEntity*>* dest_room_players = dest_room->GetPlayerVector();
	for (int i = 0; i < dest_room_players->size(); i++)
	{
		Player* room_player = dynamic_cast<Player*>(dest_room_players->at(i));
		Message* entrance_msg = new Message(player->GetName() + " entered the area.", room_player->GetConnectionId(), Message::outputMessage);
		parent->PutMessage(entrance_msg);
	}

	// add player to destination room list
	dest_room->AddPlayer(player);


	// send room description to player
	std::string description = dest_room->GetDescription();

	// create message
	Message* player_msg = new Message(description, connection_id, Message::outputMessage);

	// place message on message buffer
	parent->PutMessage(player_msg);
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
	Room* room = FindPlayerRoom(player);

	// send exit to other players in room
	std::vector<GameEntity*>* room_players = room->GetPlayerVector();
	for (int i = 0; i < room_players->size(); i++)
	{
		Player* room_player = dynamic_cast<Player*>(room_players->at(i));
		Message* msg = new Message(player->GetName() + " said " + words, room_player->GetConnectionId(), Message::outputMessage);
		parent->PutMessage(msg);
	}
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

	// send exit to other players in game
	std::vector<int>* current_player_ids = current_players_->GetIdVector();
	for (int i = 0; i < current_player_ids->size(); i++)
	{
		int id = current_player_ids->at(i);
		Player* game_player = dynamic_cast<Player*>(players_->GetEntity(id));
		Message* msg = new Message(player->GetName() + " shouted " + words, game_player->GetConnectionId(), Message::outputMessage);
		parent->PutMessage(msg);
	}
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
	Room* room = FindPlayerRoom(player);

	// find other player
	GameEntity* other_pentity = room->FindEntity(player_name);

	// try to cast to item type
	Player* other_player = dynamic_cast<Player*>(other_pentity);

	// send you those words
	Message* pmsg = new Message(player->GetName() + " whispered " + words, player->GetConnectionId(), Message::outputMessage);
	parent->PutMessage(pmsg);

	// send player those words
	Message* omsg = new Message(player->GetName() + " whispered " + words, other_player->GetConnectionId(), Message::outputMessage);
	parent->PutMessage(omsg);
}

/**
* Player command
* Take command with a given entity
* Adds room item to the players inventory
*/
void GameWorld::Take(int connection_id, std::string entity)
{
	// find player
	Player* player = FindPlayer(connection_id);

	// find room
	Room* room = FindPlayerRoom(player);

	// find item
	GameEntity* ientity = room->FindEntity(entity);

	// try to cast to item type
	Item* item = dynamic_cast<Item*>(ientity);

	// add item to player item list
	player->AddItem(item);

	Message* msg = new Message(entity + " was added to your inventory", connection_id, Message::outputMessage);
	parent->PutMessage(msg);
}

/**
* Player command
* Help command
* Returns a list of commands for the player
*/
void GameWorld::Help(int connection_id)
{
	std::string help = "Help is on its way!\n";
	help += "\n";
	help += "Commands are:\n";
	help += "-look\n";
	help += "-move\n";
	help += "-say\n";
	help += "-shout\n";
	help += "-whisper\n";
	help += "-take\n";
	help += "-signup\n";
	help += "-login\n";
	help += "-logout\n";
	help += "\n";
	help += "Enjoy the game.\n";
	help += "Please, forget you saw this.\n";
	Message* msg = new Message(help, connection_id, Message::outputMessage);
	parent->PutMessage(msg);
}

/**
* Player command
* Signup command
* Registers login name with password in the player list in game world
*/
void GameWorld::SignUp(int connection_id, std::string login_name, std::string password)
{
	// construct player
	Player* player = new Player(players_->GetNextId(), login_name, password);

	// add to player list
	players_->AddEntity(player);

	// message player
	Message* msg = new Message("You created new life. Please login...", connection_id, Message::outputMessage);
	parent->PutMessage(msg);
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
	if (player->GetPassword() != password)
	{
		Message* msg = new Message("Wrong username/password!", connection_id, Message::outputMessage);
		return;
	}

	// place into current players list
	current_players_->AddConnection(connection_id, player->GetId());
	player->SetConnectionId(connection_id);

	// get player room, place into room player list
	Room* room = FindPlayerRoom(player);
	room->AddPlayer(player);

	// send login to other players in room
	std::vector<GameEntity*>* room_players = room->GetPlayerVector();
	for (int i = 0; i < room_players->size(); i++)
	{
		Player* room_player = dynamic_cast<Player*>(room_players->at(i));
		Message* msg = new Message(player->GetName() + " phased into reality.", room_player->GetConnectionId(), Message::outputMessage);
		parent->PutMessage(msg);
	}
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
	player->SetConnectionId(-1);

	// remove player from room list
	Room* room = FindPlayerRoom(player);

	// send logout to players in room
	std::vector<GameEntity*>* room_players = room->GetPlayerVector();
	for (int i = 0; i < room_players->size(); i++)
	{
		Player* room_player = dynamic_cast<Player*>(room_players->at(i));
		Message* msg = new Message(player->GetName() + " returned to a dream.", room_player->GetConnectionId(), Message::outputMessage);
		parent->PutMessage(msg);
	}

	room->RemovePlayer(player->GetId());
}
