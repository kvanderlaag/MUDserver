#include "GameWorld.h"
#include "FileParser.h"

#include <iostream>
#include <sstream>
#include <fstream>

/**
* Create a game world, with entity lists for players and rooms
*/
GameWorld::GameWorld(Server* par) :
	parent(par),
	players_(new EntityList()),
	rooms_(new EntityList()),
	items_(new EntityList()),
	current_players_(new ConnectionList())
{
#ifdef _DEBUG_FLAG
    std::cout << "Created a world..." << std::endl;
#endif

	std::vector<std::string>* players = FileParser::ParseFile("players.tsv");
#ifdef _DEBUG_FLAG
	std::cout << "Loading players..." << std::endl;
#endif
	for (size_t i = 0; i < players->size(); ++i) {
		std::vector<std::string>* player_values = FileParser::ParseTsv(players->at(i));
		std::string name = player_values->at(0);
		std::string password = player_values->at(1);
		
		Player* player = new Player(players_->GetNextId(), name, password);

		// add to player list
		players_->AddEntity(player);
	}

	std::vector<std::string>* rooms = FileParser::ParseFile("rooms.tsv");

#ifdef _DEBUG_FLAG
	std::cout << "Loading Rooms...";
#endif
	for (int i = 0; i != rooms->size(); i++) {

		std::vector<std::string>* room_values = FileParser::ParseTsv(rooms->at(i));
		std::string name = room_values->at(0);
		std::string description = room_values->at(1);
		

		Room* room = new Room(rooms_->GetNextId(), name, description);
		rooms_->AddEntity(room);
	}
#ifdef _DEBUG_FLAG
	std::cout << "DONE" << std::endl;


	std::cout << "Loading Exits...";
#endif
	for (int i = 0; i != rooms->size(); i++) {

		std::vector<std::string>* room_values = FileParser::ParseTsv(rooms->at(i));
		std::string name = room_values->at(0);
		std::vector<std::string>* exits = FileParser::ParseCsv(room_values->at(2));
		std::vector<std::string>* directions = FileParser::ParseCsv(room_values->at(3));

		Room* room = dynamic_cast<Room*>(rooms_->FindEntity(name));
		//room->Print();

		if (room_values->size() > 4) {
			std::vector<std::string>* items = FileParser::ParseCsv(room_values->at(4));
			for each (std::string item_desc in *items) {
				Item* i = new Item(items_->GetNextId(), item_desc);
				room->AddItem(i);
			}
		}


		for (int j = 0; j != exits->size(); j++) {
			std::string exit_name = exits->at(j);
			std::string exit_dir = directions->at(j);

			Room* exit_room = dynamic_cast<Room*>(rooms_->FindEntity(exit_name));

			if (exit_room)
			{
				room->AddExit(exit_room);
				room->AddDirection(exit_room->GetId(), exit_dir);
			}
		}
	}
#ifdef _DEBUG_FLAG
	std::cout << "DONE" << std::endl;
#endif
}


/**
* Destroy a game world
*/
GameWorld::~GameWorld()
{
	FileParser::WritePlayers("players.tsv", players_->GetEntityVector());
#ifdef _DEBUG_FLAG
	std::cout << "Destroyed a world..." << std::endl;
#endif
}

/**
* Add a room to the room list in game world
*/
void GameWorld::AddRoom(Room *room)
{
#ifdef _DEBUG_FLAG
	std::cout << "Added a room" << std::endl;
#endif
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
* Receive a message and handle it
*/
void GameWorld::ReceiveMessage(Message* message)
{
	std::stringstream iss(message->Read());

	std::string command;
	std::string words;
	iss >> command;
	iss.get();
	std::getline(iss, words);

#ifdef _DEBUG_FLAG
	std::cout << "World receiving message." << std::endl;
	std::cout << "command: " << command << std::endl;
#endif

	if (command == "help")
	{
		Help(message->GetSource());
	}
	else if (command == "login")
	{
		std::stringstream wss(words);
		std::string username;
		std::string password;
		wss >> username;
		wss >> password;

		LogIn(message->GetSource(), username, password);
	}
	else if (command == "look")
	{
		std::stringstream wss(words);
		std::string entity;
		std::getline(wss, words);

		if (entity.length() > 0)
			Look(message->GetSource(), entity);
		else
			Look(message->GetSource());
	}
	else if (command == "move")
	{
		Move(message->GetSource(), words);
	}
	else if (command == "shout") {
		Shout(message->GetSource(), words);
	}
	else if (command == "say")
	{
		Say(message->GetSource(), words);
	}
	else if (command == "signup")
	{
#ifdef _DEBUG_FLAG
		std::cout << "Signing Up";
#endif
		std::stringstream wss(words);
		std::string username;
		std::string password;
		wss >> username;
		wss >> password;

		SignUp(message->GetSource(), username, password);
	}
	/*else if (command == "take")
	{
		std::stringstream wss(words);
		std::string entity;
		wss >> entity;

		Take(message->GetSource(), entity);
	}*/
	else if (command == "whisper")
	{
		std::stringstream wss(words);
		std::string player;
		std::string whisp;
		wss >> player;
		wss.get();
		std::getline(wss, whisp);

		Whisper(message->GetSource(), player, whisp);
	}
	else if (command == "north" || command == "south" || command == "east" || command == "west") {
		Move(message->GetSource(), command);
	}
	else if (command == "shutdown") {
		Player* p = FindPlayer(message->GetSource());
		if (p) {
			if (p->GetName() == "Keegan") {
#ifdef _DEBUG_FLAG
				std::cout << "Do shutdown." << std::endl;
#endif
				parent->GetListener()->Shutdown();
			}
		}
		else {
			Message* msg = new Message("Invalid command. Type \"help\" for list of valid commands.", message->GetSource(), Message::outputMessage);
			parent->PutMessage(msg);
		}
	}
	else {
		Message* msg = new Message("Invalid command. Type \"help\" for list of valid commands.", message->GetSource(), Message::outputMessage);
		parent->PutMessage(msg);

	}
}

/**
* Player command
* Help command
* Returns a list of commands for the player
*/
void GameWorld::Help(int connection_id)
{
	std::string help = "Help is on its way!\n\r";
	help += "\n\r";
	help += "Commands are:\n\r";
	help += "look <target>\n\r";
	help += "move <exit>\n\r";
	help += "say <message>\n\r";
	help += "shout <message>\n\r";
	help += "whisper <target> <message>\n\r";
	//help += "take <target>\n\r";
	help += "quit\n\r";
	help += "\n\r";
	help += "Enjoy the game. :D\n\r";
	help += "Please, forget you saw this.\n\r";
	Message* msg = new Message(help, connection_id, Message::outputMessage);
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
	// player is already logged in
	if (current_players_->GetPlayerId(connection_id) != -1)
	{
		// message player
		Message* msg = new Message("You're already logged in...", connection_id, Message::outputMessage);
		parent->PutMessage(msg);
		return;
	}

	GameEntity* pentity = players_->FindEntity(login_name);
	if (pentity == NULL)
	{
		Message* msg = new Message("Wrong username/password!", connection_id, Message::outputMessage);
		parent->PutMessage(msg);
		return;
	}

	int con = ( (Player*) pentity )->GetConnectionId();
	if (con != -1) {
		Message* msg = new Message("User is already logged in.", connection_id, Message::outputMessage);
		parent->PutMessage(msg);
		return;
	}

	Player* player = dynamic_cast<Player*>(pentity);
	player->Print();

	// check password
	if (player->GetPassword() != password)
	{
		Message* msg = new Message("Wrong username/password!", connection_id, Message::outputMessage);
		parent->PutMessage(msg);
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
	for (std::size_t i = 0; i < room_players->size(); i++)
	{
		Player* room_player = dynamic_cast<Player*>(room_players->at(i));
		Message* msg = new Message(player->GetName() + " phased into reality.", room_player->GetConnectionId(), Message::outputMessage);
		parent->PutMessage(msg);
	}

	Look(player->GetConnectionId());
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
	Player* player = FindPlayer(connection_id);
	if (player != nullptr) {
		player->SetConnectionId(-1);

		current_players_->RemoveConnection(connection_id);

		// remove player from room list
		Room* room = FindPlayerRoom(player);

		// send logout to players in room
		std::vector<GameEntity*>* room_players = room->GetPlayerVector();
		for (std::size_t i = 0; i < room_players->size(); i++)
		{
			Player* room_player = dynamic_cast<Player*>(room_players->at(i));
			Message* msg = new Message(player->GetName() + " returned to a dream.", room_player->GetConnectionId(), Message::outputMessage);
			parent->PutMessage(msg);
		}

		room->RemovePlayer(player->GetId());
	}
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

	// Get exits
	std::ostringstream exits;

	exits << cGreen << "Exits are:\n\r" << cDefault;
	std::map<int, std::string>* vExits = room->GetExitVector();
	std::map<int, std::string>::iterator it = vExits->begin();
	if (it == vExits->end()) {
		exits << "None.";
	}
	else {
		for (it; it != vExits->end(); it++) {
			exits << it->second << " ";
		}
		exits << "\n\r";
	}

	// Get items
	std::ostringstream items;

	items << cGreen << "Items here:\n\r" << cDefault;
	std::vector<Item*>* vItems = (std::vector<Item*>*) room->GetItemVector();
	if (vItems->empty()) {
		items << "None.\n\r";
	}
	else {
		for each (Item* i in *vItems) {
			items << i->GetName() << "\n\r";
		}
	}

	
	// Get players
	std::ostringstream players;
	players << cGreen << "The following people are here:\n\r" << cDefault;
	std::vector<Player*>* vPlayers = (std::vector<Player*>*) room->GetPlayerVector();
	if (vPlayers->size() > 1) {
		for (size_t i = 0; i < vPlayers->size(); ++i) {
			if (vPlayers->at(i)->GetName() != player->GetName()) {
				players << vPlayers->at(i)->GetName() << "\n\r";
			}
		}
	}
	else {
		players << "None.";
	}

	// create message
	std::ostringstream output;
	output << "\n\r" << cBlue << "---\n\r" << cYellow << room->GetName() << cBlue << "\n\r---\n\r" << cDefault << description << cBlue << "\n\r---\n\r" << cDefault << exits.str() << cBlue << "---\n\r" << cDefault << items.str() << cBlue << "---\n\r" << cDefault << players.str() << "\n\r";
	Message* msg = new Message(output.str(), player->GetConnectionId(), Message::outputMessage);

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

	if (entity != NULL)
	{
		// get description
		std::string description = entity->GetDescription();

		// create message
		Message* msg = new Message(description, player->GetConnectionId(), Message::outputMessage);

		// place msg on message buffer
		parent->PutMessage(msg);
	}
	else
	{
		// send no entity message
		Message* msg = new Message("There is no such thing to look at...", player->GetConnectionId(), Message::outputMessage);

		// place msg on message buffer
		parent->PutMessage(msg);
	}
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

	if (dest_room != NULL)
	{
		// remove player from current room list
		current_room->RemovePlayer(player->GetId());

		// send exit to other players in room
		std::vector<GameEntity*>* current_room_players = current_room->GetPlayerVector();
		for (std::size_t i = 0; i < current_room_players->size(); i++)
		{
			Player* room_player = dynamic_cast<Player*>(current_room_players->at(i));
			Message* exit_msg = new Message(player->GetName() + " headed " + exit + " towards " + dest_room->GetName() + ".", room_player->GetConnectionId(), Message::outputMessage);
			parent->PutMessage(exit_msg);
		}


		// send entrance to other players in new room
		std::vector<GameEntity*>* dest_room_players = dest_room->GetPlayerVector();
		for (std::size_t i = 0; i < dest_room_players->size(); i++)
		{
			Player* room_player = dynamic_cast<Player*>(dest_room_players->at(i));
			Message* entrance_msg = new Message(player->GetName() + " entered the area.", room_player->GetConnectionId(), Message::outputMessage);
			parent->PutMessage(entrance_msg);
		}

		// add player to destination room list
		dest_room->AddPlayer(player);
		player->SetRoomId(dest_room->GetId());

		// send room description to player
		std::string description = dest_room->GetDescription();

		// create message
		Look(player->GetConnectionId());
	}
	else
	{
		// send no room message
		Message* player_msg = new Message("There is no such place to move to...", player->GetConnectionId(), Message::outputMessage);

		// place message on message buffer
		parent->PutMessage(player_msg);
	}
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
	for (std::size_t i = 0; i < room_players->size(); i++)
	{
		Player* room_player = dynamic_cast<Player*>(room_players->at(i));
		Message* msg = new Message(player->GetName() + " said \"" + words + "\"", room_player->GetConnectionId(), Message::outputMessage);
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

	// send meesage to other players in game
	std::vector<int>* current_player_ids = current_players_->GetIdVector();
	for (std::size_t i = 0; i < current_player_ids->size(); i++)
	{
		int id = current_player_ids->at(i);
		Player* game_player = dynamic_cast<Player*>(players_->GetEntity(id));
		Message* msg = new Message(player->GetName() + " shouts \"" + words +"\"", game_player->GetConnectionId(), Message::outputMessage);
		parent->PutMessage(msg);
	}
}

/**
* Player command
* Signup command
* Registers login name with password in the player list in game world
*/
void GameWorld::SignUp(int connection_id, std::string login_name, std::string password)
{
	// player is already logged in
	if (current_players_->GetPlayerId(connection_id) != -1)
	{
		// message player
		Message* msg = new Message("You're already logged in...", connection_id, Message::outputMessage);
		parent->PutMessage(msg);
		return;
	}
	// find player
	else if (players_->FindEntity(login_name))
	{
		// message player
		Message* msg = new Message("That person already exists...", connection_id, Message::outputMessage);
		parent->PutMessage(msg);
	}
	else
	{
		// construct player
		Player* player = new Player(players_->GetNextId(), login_name, password);

		// add to player list
		players_->AddEntity(player);

		// message player
		Message* msg = new Message("You created new life. Please login...", connection_id, Message::outputMessage);
		parent->PutMessage(msg);
	}
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

	if (item != NULL)
	{
		// add item to player item list
		player->AddItem(item);

		Message* msg = new Message(entity + " was added to your inventory", player->GetConnectionId(), Message::outputMessage);
		parent->PutMessage(msg);
	}
	else
	{
		// no item message
		Message* msg = new Message("There is no such thing to take...", player->GetConnectionId(), Message::outputMessage);
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

	if (other_player != NULL)
	{
		// send you those words
		Message* pmsg = new Message("You whisper \"" + words + "\" to " + other_player->GetName(), player->GetConnectionId(), Message::outputMessage);
		parent->PutMessage(pmsg);

		// send player those words
		Message* omsg = new Message(player->GetName() + " whispers \"" + words + "\"", other_player->GetConnectionId(), Message::outputMessage);
		parent->PutMessage(omsg);
	}
	else
	{
		// send no player message
		Message* player_msg = new Message("There is no such person to whisper to...", player->GetConnectionId(), Message::outputMessage);

		// place message on message buffer
		parent->PutMessage(player_msg);
	}
}
