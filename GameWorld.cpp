#include "GameWorld.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>

bool GameWorld::running = true;

/**
* Create a game world, with entity lists for players and rooms
*/
GameWorld::GameWorld(Server& par) :
	parent(par),
	players_(new EntityList()),
	rooms_(new EntityList()),
	items_(new EntityList()),
	mobs_(new EntityList()),
	current_players_(new ConnectionList()),
	master_items_(new EntityList()),
	master_mobs_(new EntityList()),
	battles_(new BattleList(this)),
	character_classes_(new CharacterClassList(this))
{
#ifdef _DEBUG_FLAG
	std::cout << "Created a world..." << std::endl;
#endif
	memento->GetState();

}


/**
* Destroy a game world
*/
GameWorld::~GameWorld()
{
	memento->SetState();
	std::cout << "Destroyed a world..." << std::endl;
}

/**
* Add a room to the room list in game world
*/
void GameWorld::AddRoom(Room& room)
{
#ifdef _DEBUG_FLAG
	std::cout << "Added a room" << std::endl;
#endif
	rooms_->AddEntity(room);
}

/**
* Add a player to the player list in game world
*/
void GameWorld::AddPlayer(Player& player)
{
	players_->AddEntity(player);
}

void GameWorld::AddMob(NPC & entity)
{
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

void GameWorld::RemoveMob(NPC & entity)
{
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
	if (pentity) {
		Player* player = dynamic_cast<Player*>(pentity);

		return player;
	}
	return nullptr;
}

/**
* Get the room object given the player object
*/
Room* GameWorld::FindPlayerRoom(Player& player)
{
	// find room id
	int rid = player.GetRoomId();
	// find room
	GameEntity* rentity = rooms_->GetEntity(rid);
	Room* room = dynamic_cast<Room*>(rentity);

	return room;
}

/**
* Find the NPC object given the NPC ID.
*/
NPC* GameWorld::FindMob(int mobId)
{
	// find NPC
	GameEntity* mentity = mobs_->GetEntity(mobId);
	if (mentity) {
		NPC* mob = dynamic_cast<NPC*>(mentity);

		return mob;
	}
	return nullptr;
}

/**
* Get the room object given the NPC object
*/
Room* GameWorld::FindMobRoom(NPC& mob)
{
	// find room id
	int rid = mob.GetRoomId();
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
	Player* player = FindPlayer(message->GetSource());
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

	if (!player) {
		if (command == "login")
		{
			std::stringstream wss(words);
			std::string username;
			std::string password;
			wss >> username;
			wss >> password;

			LogIn(message->GetSource(), username, password);
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
		else {
			std::ostringstream outString;
			outString << "Invalid command. Either\n" << cGreen << "login" << cDefault << " <username> <password>\n-or-\n" << cGreen << "signup" << cDefault << " <username> <password>\n";
			Message* msg = new Message(outString.str(), message->GetSource(), Message::outputMessage);
			parent.PutMessage(msg);
		}
	}
	else {
		if (command == "attack" || command == "a") {
			Attack(message->GetSource(), words);
		}
		else if (command == "help" || command == "h")
		{
			Help(message->GetSource());
		}
		else if (command == "look")
		{
			std::stringstream wss(words);
			std::string entity;
			std::getline(wss, words);

			if (!words.empty())
				Look(message->GetSource(), words);
			else
				Look(message->GetSource());
		}
		else if (command == "move")
		{
			if (!battles_->GetBattleByPlayerId(player->GetId())) {
				Move(message->GetSource(), words);
			}
		}
		else if (command == "shout") {
			Shout(message->GetSource(), words);
		}
		else if (command == "say")
		{
			Say(message->GetSource(), words);
		}
		else if (command == "take" || command == "get")
		{
			std::stringstream wss(words);
			std::string entity;
			wss >> entity;

			Take(message->GetSource(), words);
		}
		else if (command == "tell" || command == "t") {
			std::stringstream wss(words);
			std::string player;
			std::string tell;
			wss >> player;
			wss.get();
			std::getline(wss, tell);

			Tell(message->GetSource(), player, tell);
		}
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
		else if (command == "who") {
			Who(message->GetSource());
		}
		else if (command == "n" || command == "s" || command == "e" || command == "w") {
			if (!battles_->GetBattleByPlayerId(player->GetId())) {
				if (command == "n")
					Move(message->GetSource(), "north");
				if (command == "s")
					Move(message->GetSource(), "south");
				if (command == "e")
					Move(message->GetSource(), "east");
				if (command == "w")
					Move(message->GetSource(), "west");
			}
		}
		else if (command == "north" || command == "south" || command == "east" || command == "west") {
			if (!battles_->GetBattleByPlayerId(player->GetId())) {
				Move(message->GetSource(), command);
			}
			else {
				std::ostringstream outString;
				outString << "You can't do that while you're in combat!";
				Message* outMsg = new Message(outString.str(), message->GetSource(), Message::outputMessage);
				parent.PutMessage(outMsg);
			}
		}
		else if (command == "inventory" || command == "i" || command == "inv") {
			DisplayInventory(message->GetSource());
		}
		else if (command == "drop" || command == "d") {
			Drop(message->GetSource(), words);
		}
		else if (command == "password") {
			Password(message->GetSource(), words);
		}
		else if (command == "shutdown") {
				if (player->GetName() == "Keegan") {
#ifdef _DEBUG_FLAG
					std::cout << "Do shutdown." << std::endl;
#endif
					parent.GetListener()->Shutdown();
				}
				else {
					std::ostringstream outString;
					outString << "Invalid command. Type \"" << cGreen << "help" << cDefault << "\" for a list of valid commands.";
					Message* msg = new Message(outString.str(), message->GetSource(), Message::outputMessage);
					parent.PutMessage(msg);
				}
		}
		else if (command == "desc" || command == "description") {
			Description(message->GetSource(), words);
		}
		else if (command == "stats" || command == "statistics" || command == "st" || command == "sc" || command == "score") {
			Stats(message->GetSource());
		}
		else {
			std::ostringstream outString;
			outString << "Invalid command. Type \"" << cGreen << "help" << cDefault << "\" for a list of valid commands.";
			Message* msg = new Message(outString.str(), message->GetSource(), Message::outputMessage);
			parent.PutMessage(msg);
		}
	}
}

/**
* Player command
* Attacks the specified target if not already in combat
* Switches target if currently in combat.
*/
void GameWorld::Attack(int connection_id, std::string entity) {
	Player* p = FindPlayer(connection_id);
	if (!p) {
		return;
	}
	Battle* b = battles_->GetBattleByPlayerId(p->GetId());
	if (!b) {
		Battle* m = battles_->GetBattleByMobName(entity);
		if (!m) {
			Room* r = FindPlayerRoom(*p);
			NPC* mob = (NPC*) r->FindMob(entity);
			if (mob) {
				Battle* newBattle = new Battle(battles_->GetNextId(), this);
				newBattle->AddPlayer(p, mob);
				newBattle->AddMob(mob, p);
				battles_->AddBattle(newBattle);

				std::ostringstream outString;
				outString << "You enter combat with " << cGreen << mob->GetName() << cDefault << "!";
				Message* outMsg = new Message(outString.str(), p->GetConnectionId(), Message::outputMessage);
				parent.PutMessage(outMsg);
			}
			else {
				std::ostringstream outString;
				outString << cGreen << entity << cDefault << "is not here.";
				Message* outMsg = new Message(outString.str(), p->GetConnectionId(), Message::outputMessage);
				parent.PutMessage(outMsg);
				// print message saying no mob was found
			}

		}
		else {
			NPC* mob = m->GetMobByName(entity);
			m->AddPlayer(p, mob);
			std::ostringstream outString;
			outString << "You enter combat with " << cGreen << mob->GetName() << cDefault << "!";
			Message* outMsg = new Message(outString.str(), p->GetConnectionId(), Message::outputMessage);
			parent.PutMessage(outMsg);
		}
	}
	else {
		b->SetTarget(p, b->GetMobByName(entity));
		if (NPC* mob = b->GetMobByName(entity)) {
			std::ostringstream outString;
			outString << "You change targets to " << cGreen << mob->GetName() << cDefault << ".";
			Message* outMsg = new Message(outString.str(), p->GetConnectionId(), Message::outputMessage);
			parent.PutMessage(outMsg);
		}
		else {
			std::ostringstream outString;
			outString << "You aren't fighting " << cGreen << entity << cDefault << "!";
			Message* outMsg = new Message(outString.str(), p->GetConnectionId(), Message::outputMessage);
			parent.PutMessage(outMsg);
		}
	}
}

/**
* Player Command
* Shows current player's inventory
*/
void GameWorld::DisplayInventory(int connection_id) {
	Player* p = FindPlayer(connection_id);
	std::vector<GameEntity*> inv = p->GetItemVector();
	std::ostringstream displayString;
	displayString << "\n" << cGreen << "Current inventory:" << "\n" << cDefault;
	if (inv.empty()) {
		displayString << "Nothing.\n";
	}
	else {
		for (GameEntity* item : inv) {
			displayString << item->GetName() << "\n";
		}
	}

	Message* outMessage = new Message(displayString.str(), connection_id, Message::MessageType::outputMessage);
	parent.PutMessage(outMessage);
}


/**
* Player Command
* Drops specified item into room, if present in inventory.
*/
void GameWorld::Drop(int connection_id, std::string entity) {
	Player* p = FindPlayer(connection_id);
	Room* r = FindPlayerRoom(*p);

	std::ostringstream playerOutputString;
	std::ostringstream roomOutputString;

	Item* i = (Item*) p->FindItem(entity);
	if (!i) {
		playerOutputString << "You don't have " << cGreen << entity << cDefault << " in your inventory!\n";
		Message* playerMessage = new Message(playerOutputString.str(), connection_id, Message::MessageType::outputMessage);
		parent.PutMessage(playerMessage);
		return;
	}
	p->RemoveItem(i->GetId());
	r->AddItem(*i);
	playerOutputString << "You drop " << cGreen << i->GetName() << cDefault << ".\n";
	roomOutputString << cYellow << p->GetName() << cDefault << " drops " << cGreen << i->GetName() << cDefault << ".\n";
	Message* playerMessage = new Message(playerOutputString.str(), connection_id, Message::MessageType::outputMessage);
	parent.PutMessage(playerMessage);
	std::vector<GameEntity*> roomPlayers = r->GetPlayerVector();
	for (GameEntity* p : roomPlayers) {
		if (((Player* )p)->GetConnectionId() != connection_id) {
			Message* roomMessage = new Message(roomOutputString.str(), ((Player* )p)->GetConnectionId(), Message::MessageType::outputMessage);
			parent.PutMessage(roomMessage);
		}
	}



}


/**
* Player command
* Help command
* Returns a list of commands for the player
*/
void GameWorld::Help(int connection_id)
{
	std::ostringstream help;
	help << "Help is on its way!\n";
	help << "\n";
	help << "Commands are:\n";
	help << cGreen << "drop" << cDefault << " <target> -or- " << cGreen << "d" << cDefault << " <target>\n";
	help << cGreen << "inventory" << cDefault << " -or- " << cGreen << "inv" << cDefault << " -or- " << cGreen << "i" << cDefault << "\n";
	help << cGreen << "look" << cDefault << " <target>\n";
	help << cGreen << "move" << cDefault << " <exit>\n";
	help << cGreen << "password" << cDefault << " <new password>\n";
	help << cGreen << "quit\n" << cDefault;
	help << cGreen << "say" << cDefault << " <message>\n";
	help << cGreen << "stats" << cDefault << " -or - " << cGreen << "score\n";
	help << cGreen << "shout" << cDefault << " <message>\n";
	help << cGreen << "tell" << cDefault << "<target>\n";
	help << cGreen << "take" << cDefault << " <target> -or- " << cGreen << "get" << cDefault << " <target>\n";
	help << cGreen << "whisper" << cDefault << " <target> <message>\n";
	help << cGreen << "who" << cDefault << "\n";

	help << "\n";
	help << "Compass directions north, south, east, and west can be used as commands,\nand shorten to n, s, e, and w.";
	help << "\n\n";
	help << "Enjoy the game. :D\n";
	Message* msg = new Message(help.str(), connection_id, Message::outputMessage);
	parent.PutMessage(msg);
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

	GameEntity* pentity = players_->FindEntity(login_name);
	if (!pentity)
	{
		Message* msg = new Message("Wrong username/password!", connection_id, Message::outputMessage);
		parent.PutMessage(msg);
		return;
	}

	int con = ( (Player*) pentity )->GetConnectionId();
	if (con != -1) {
		Message* msg = new Message("User is already logged in.", connection_id, Message::outputMessage);
		parent.PutMessage(msg);
		return;
	}

	Player* player = dynamic_cast<Player*>(pentity);
	//player->Print();

	// check password
	if (player->GetPassword() != password)
	{
		Message* msg = new Message("Wrong username/password!", connection_id, Message::outputMessage);
		parent.PutMessage(msg);
		return;
	}

	// place into current players list
	current_players_->AddConnection(connection_id, player->GetId());
	player->SetConnectionId(connection_id);

	// get player room, place into room player list
	Room* room = FindPlayerRoom(*player);
	room->AddPlayer(*player);

	// send login to other players in room
	std::vector<GameEntity*> room_players = room->GetPlayerVector();
	for (std::size_t i = 0; i < room_players.size(); i++)
	{
		Player* room_player = dynamic_cast<Player*>(room_players.at(i));
		std::ostringstream outString;
		outString << cGreen << player->GetName() << cDefault << " phased into reality.";
		Message* msg = new Message(outString.str(), room_player->GetConnectionId(), Message::outputMessage);
		parent.PutMessage(msg);
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
	if (player) {
		player->SetConnectionId(-1);

		current_players_->RemoveConnection(connection_id);

		// remove player from room list
		Room* room = FindPlayerRoom(*player);

		// send logout to players in room
		std::vector<GameEntity*> room_players = room->GetPlayerVector();
		for (std::size_t i = 0; i < room_players.size(); i++)
		{
			Player* room_player = dynamic_cast<Player*>(room_players.at(i));
			std::ostringstream outString;
			outString << cGreen << player->GetName() << cDefault << " returned to a dream.";
			Message* msg = new Message(outString.str(), room_player->GetConnectionId(), Message::outputMessage);
			parent.PutMessage(msg);
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
	Room* room = FindPlayerRoom(*player);

	// find description
	std::string description = room->GetDescription();

	// Get exits
	std::ostringstream exits;

	exits << cGreen << "Exits are:\n" << cDefault;
	std::map<int, std::string> vExits = room->GetExitVector();
	std::map<int, std::string>::iterator it = vExits.begin();
	if (it == vExits.end()) {
		exits << "None.";
	}
	else {
		for (it; it != vExits.end(); it++) {
			exits << it->second << " ";
		}
		exits << "\n";
	}

	// Get items
	std::ostringstream items;

	items << cGreen << "Items here:\n" << cDefault;
	std::vector<GameEntity*> vItems = room->GetItemVector();
	if (vItems.empty()) {
		items << "None.\n";
	}
	else {
		for (GameEntity* i : vItems) {
			items << i->GetName() << "\n";
		}
	}


	// Get players
	std::ostringstream players;
	players << cGreen << "The following people are here:\n" << cDefault;
	std::vector<GameEntity*> vPlayers = room->GetPlayerVector();
	if (vPlayers.size() > 1) {
		for (size_t i = 0; i < vPlayers.size(); ++i) {
			if (vPlayers.at(i)->GetName() != player->GetName()) {
				players << cGreen << vPlayers.at(i)->GetName() << cDefault << "\n";
			}
		}
	}
	else {
		players << "None.\n";
	}

	// Get mobs
	std::ostringstream mobs;
	mobs << cGreen << "Monsters:\n" << cDefault;
	std::vector<GameEntity*> vMobs = room->GetMobVector();
	if (vMobs.size() > 0) {
		for (size_t i = 0; i < vMobs.size(); ++i) {
			//std::cout << vMobs.at(i)->GetName() << "\n";
			mobs << cRed << vMobs.at(i)->GetName() << cDefault << "\n";
		}
	}
	else {
		mobs << "None.";
	}

	// create message
	std::ostringstream output;
	output << "\n" << cBlue << "---\n" << cYellow << room->GetName() << cBlue << "\n---\n" << cDefault <<
		description << cBlue << "\n---\n" << cDefault << exits.str() << cBlue << "---\n" << cDefault <<
		items.str() << cBlue << "---\n" << cDefault << players.str() << cBlue << "---\n" << mobs.str() << "\n";
	Message* msg = new Message(output.str(), player->GetConnectionId(), Message::outputMessage);

	// place message on message buffer
	parent.PutMessage(msg);
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
	Room* room = FindPlayerRoom(*player);

	// first check room exits
	GameEntity* rentity = room->GetExit(entity_name);

	if (rentity) {
		std::ostringstream outputString;
		outputString << "You see " << cYellow << rentity->GetName() << cDefault << ".\n";
		Message* msg = new Message(outputString.str(), connection_id, Message::outputMessage);
		parent.PutMessage(msg);
		return;
	}

	// otherwise, check items
	GameEntity* rientity = room->FindItem(entity_name);

	if (rientity) {
		std::ostringstream outputString;
		outputString << "You see " << cGreen << rientity->GetName() << cDefault << " in " << cYellow << room->GetName() << cDefault << ".\n";
		outputString << "Description:\n" << rientity->GetDescription() << "\n";
		Message* msg = new Message(outputString.str(), connection_id, Message::outputMessage);
		parent.PutMessage(msg);
		return;
	}


	// otherwise, check players
	GameEntity* pentity = room->FindPlayer(entity_name);

	if (pentity) {
		std::ostringstream outputString;
		outputString << "You see " << cGreen << pentity->GetName() << cDefault << " here with you.\n";
		outputString << "Description:\n" << pentity->GetDescription() << "\n";
		Message* msg = new Message(outputString.str(), connection_id, Message::outputMessage);
		parent.PutMessage(msg);
		return;
	}

	// otherwise, check the player's inventory for items.
	GameEntity* pientity = player->FindItem(entity_name);

	if (pientity) {
		std::ostringstream outputString;
		outputString << "You see " << cGreen << pientity->GetName() << cDefault << " in your inventory.\n";
		outputString << "Description:\n" << pientity->GetDescription() << "\n";
		Message* msg = new Message(outputString.str(), connection_id, Message::outputMessage);
		parent.PutMessage(msg);
		return;
	}

	// otherwise, check mobs
	GameEntity* mientity = room->FindMob(entity_name);

	if (mientity) {
		std::ostringstream outputString;
		outputString << "You see " << cGreen << mientity->GetName() << cDefault << " in " << cYellow << room->GetName() << cDefault << ".\n";
		outputString << "Description:\n" << mientity->GetDescription() << "\n";
		Message* msg = new Message(outputString.str(), connection_id, Message::outputMessage);
		parent.PutMessage(msg);
		return;
	}

	// otherwise, send no entity message
	std::ostringstream outputString;
	outputString << "You don't see " << cGreen << entity_name << cDefault << " here.\n";
	Message* msg = new Message(outputString.str(), player->GetConnectionId(), Message::outputMessage);

	// place msg on message buffer
	parent.PutMessage(msg);

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
	Room* current_room = FindPlayerRoom(*player);

	// find room player wants
	GameEntity* dest_rentity = current_room->GetExit(exit);
	Room* dest_room = dynamic_cast<Room*>(dest_rentity);

	if (dest_room)
	{
		// remove player from current room list
		current_room->RemovePlayer(player->GetId());

		// send exit to other players in room
		std::vector<GameEntity*> current_room_players = current_room->GetPlayerVector();
		for (std::size_t i = 0; i < current_room_players.size(); i++)
		{
			Player* room_player = dynamic_cast<Player*>(current_room_players.at(i));
			Message* exit_msg = new Message(player->GetName() + " headed " + exit + " towards " + dest_room->GetName() + ".", room_player->GetConnectionId(), Message::outputMessage);
			parent.PutMessage(exit_msg);
		}


		// send entrance to other players in new room
		std::vector<GameEntity*> dest_room_players = dest_room->GetPlayerVector();
		for (std::size_t i = 0; i < dest_room_players.size(); i++)
		{
			Player* room_player = dynamic_cast<Player*>(dest_room_players.at(i));
			Message* entrance_msg = new Message(player->GetName() + " entered the area.", room_player->GetConnectionId(), Message::outputMessage);
			parent.PutMessage(entrance_msg);
		}

		// add player to destination room list
		dest_room->AddPlayer(*player);
		player->SetRoomId(dest_room->GetId());

		// send room description to player
		std::string description = dest_room->GetDescription();

		// create message
		Look(player->GetConnectionId());
	}
	else
	{
		// send no room message
		std::ostringstream outString;
		outString << "There is no exit " << cGreen << exit << cDefault << ".";
		Message* player_msg = new Message(outString.str(), player->GetConnectionId(), Message::outputMessage);

		// place message on message buffer
		parent.PutMessage(player_msg);
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
	Room* room = FindPlayerRoom(*player);

	// send exit to other players in room
	std::vector<GameEntity*> room_players = room->GetPlayerVector();
	for (std::size_t i = 0; i < room_players.size(); i++)
	{
		Player* room_player = dynamic_cast<Player*>(room_players.at(i));
		std::ostringstream outString;
		outString << cGreen << player->GetName() << cDefault << " says \"" << words << "\"";
		Message* msg = new Message(outString.str(), room_player->GetConnectionId(), Message::outputMessage);
		parent.PutMessage(msg);
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
	std::vector<int> current_player_ids = current_players_->GetIdVector();
	for (std::size_t i = 0; i < current_player_ids.size(); i++)
	{
		int id = current_player_ids.at(i);
		Player* game_player = dynamic_cast<Player*>(players_->GetEntity(id));
		Message* msg = new Message(player->GetName() + " shouts \"" + words +"\"", game_player->GetConnectionId(), Message::outputMessage);
		parent.PutMessage(msg);
	}
}

/**
* Player command
* Shows current player statistics
*/
void GameWorld::Stats(int connection_id) {
	Player* p = FindPlayer(connection_id);
	if (p) {
		return;
	}

	std::ostringstream outString;
	outString << cBlue << "\nStats for " << cGreen << p->GetName() << cDefault << "\n";
	outString << p->GetStats().Print();
	Message* msg = new Message(outString.str(), connection_id, Message::outputMessage);
	parent.PutMessage(msg);
}

/**
* Player command
* Signup command
* Registers login name with password in the player list in game world
*/
void GameWorld::SignUp(int connection_id, std::string login_name, std::string password)
{
	// find player
	if (players_->FindEntity(login_name))
	{
		// message player
		std::ostringstream outString;
		outString << "Character \"" << cGreen << login_name << cDefault << "\" already exists!";
		Message* msg = new Message(outString.str(), connection_id, Message::outputMessage);
		parent.PutMessage(msg);
	}
	else if (!login_name.empty() && !password.empty())
	{
		// construct player
		Player* player = new Player(players_->GetNextId(), login_name, password, this);

		// add to player list
		players_->AddEntity(*player);

		// message player
		std::ostringstream outString;
		outString << "Created character \"" << cGreen << login_name << cDefault << ".\" You may now log in.";
		Message* msg = new Message(outString.str(), connection_id, Message::outputMessage);
		parent.PutMessage(msg);
	}
	else {
		std::ostringstream outString;
		outString << "Invalid username or password.";
		Message* msg = new Message(outString.str(), connection_id, Message::outputMessage);
		parent.PutMessage(msg);
	}
}

/**
* Player command
* Shows currently logged in users.
*/
void GameWorld::Who(int connection_id) {
	std::ostringstream outString;
	outString << "\n" << cBlue << "---\n" << cGreen << "Players currently logged in:\n" << cBlue << "---" << cDefault;
	std::vector<int> players = current_players_->GetIdVector();
	for (int id : players) {
		Player* p = (Player*) GetPlayer(id);
		outString << "\n" << p->GetName();
	}
	outString << cBlue << "\n---" << cDefault << "\n";

	Message* msg = new Message(outString.str(), connection_id, Message::outputMessage);
	parent.PutMessage(msg);
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
	Room* room = FindPlayerRoom(*player);

	// find item
	Item* item = dynamic_cast<Item*>(room->FindItem(entity));

	if (item)
	{
		// add item to player item list
		player->AddItem(*item);
		room->RemoveItem(item->GetId());
		std::ostringstream outString, roomString;
		outString << "You take " << cGreen << item->GetName() << cDefault << ".\n";
		roomString << cGreen << player->GetName() << cDefault << " takes " << cGreen << item->GetName() << cDefault << ".\n";
		Message* msg = new Message(outString.str(), player->GetConnectionId(), Message::outputMessage);
		parent.PutMessage(msg);
		std::vector<GameEntity*> otherPlayers = room->GetPlayerVector();
		for (GameEntity* p : otherPlayers) {
			if (p != player) {

				Message* roomMsg = new Message(roomString.str(), ((Player*) p)->GetConnectionId(), Message::outputMessage);
				parent.PutMessage(roomMsg);
			}
		}
	}
	else
	{
		// no item message
		std::ostringstream outString;
		outString << "There is no " << cGreen << entity << cDefault << " here.\n";
		Message* msg = new Message(outString.str(), player->GetConnectionId(), Message::outputMessage);
		parent.PutMessage(msg);
	}

}

/**
* Player command
* Sets current player's description for others to see.
*/
void GameWorld::Description(int connection_id, std::string words) {
	Player* player = FindPlayer(connection_id);
	if (player) {
		return;
	}
	player->SetDescription(words);

	std::ostringstream outString;
	outString << "Your new description is \"" << cYellow << words << cDefault << "\"";
	Message* msg = new Message(outString.str(), connection_id, Message::outputMessage);
	parent.PutMessage(msg);
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
	Room* room = FindPlayerRoom(*player);

	// find other player
	GameEntity* other_pentity = room->FindEntity(player_name);

	// try to cast to item type
	Player* other_player = dynamic_cast<Player*>(other_pentity);

	if (other_player)
	{
		std::stringstream playerString, targetString;
		playerString << "You whisper \"" << words << "\" to " << cGreen << other_player->GetName() << cDefault << ".";
		// send you those words
		Message* pmsg = new Message(playerString.str(), player->GetConnectionId(), Message::outputMessage);
		parent.PutMessage(pmsg);

		// send player those words
		targetString << cGreen << other_player->GetName() << cDefault << "whispers \"" << words << "\" to you.";
		Message* omsg = new Message(targetString.str(), other_player->GetConnectionId(), Message::outputMessage);
		parent.PutMessage(omsg);
	}
	else
	{
		// send no player message
		std::stringstream errorString;
		errorString << cGreen << player_name << cDefault << " is not here.";
		Message* player_msg = new Message(errorString.str(), player->GetConnectionId(), Message::outputMessage);

		// place message on message buffer
		parent.PutMessage(player_msg);
	}
}

/**
* Player Command
* Changes the specified player's password.
*/
void GameWorld::Password(int connection_id, std::string words) {
	Player* p = FindPlayer(connection_id);

	if (p && !words.empty()) {
		p->SetPassword(words);

		std::ostringstream outString;
		outString << "Your password has been changed.";
		Message* msg = new Message(outString.str(), connection_id, Message::outputMessage);
		parent.PutMessage(msg);
	}

	memento->SetState();

}

/**
* Player command
* Tell command with a given string and player name
* Forwards this message to the specified player, if they are logged in.
*/
void GameWorld::Tell(int connection_id, std::string player_name, std::string words)
{
	// find player
	Player* player = FindPlayer(connection_id);

	// find other player
	Player* otherPlayer = (Player*) players_->FindEntity(player_name);
	if (otherPlayer) {
		if (current_players_->GetPlayerId(otherPlayer->GetConnectionId()) != -1) {
			std::stringstream playerString, targetString;
			playerString << "You tell " << cGreen << otherPlayer->GetName() << cDefault << " \"" << cYellow << words << cDefault << "\"";
			// send you those words
			Message* pmsg = new Message(playerString.str(), player->GetConnectionId(), Message::outputMessage);
			parent.PutMessage(pmsg);

			// send player those words
			targetString << cGreen << player->GetName() << cDefault << " tells you \"" << cYellow << words << cDefault << "\"";
			Message* omsg = new Message(targetString.str(), otherPlayer->GetConnectionId(), Message::outputMessage);
			parent.PutMessage(omsg);
		}
		else
		{
			// send no player message
			std::stringstream errorString;
			errorString << cGreen << otherPlayer->GetName() << cDefault << " is not there.";
			Message* player_msg = new Message(errorString.str(), player->GetConnectionId(), Message::outputMessage);

			// place message on message buffer
			parent.PutMessage(player_msg);
		}
	}
	else {
		// send no player message
		std::stringstream errorString;
		errorString << cGreen << player_name << cDefault << " does not exist.";
		Message* player_msg = new Message(errorString.str(), player->GetConnectionId(), Message::outputMessage);

		// place message on message buffer
		parent.PutMessage(player_msg);
	}
}

/**
* Create a new update processing thread
*/
void GameWorld::CreateUpdateThread(void* arg)
{
	GameWorld* instance = (GameWorld*) arg;
	instance->DoUpdate();
}

void GameWorld::CreateSaveThread(void* arg)
{
	GameWorld* instance = (GameWorld*)arg;
	instance->DoSave();
}

void GameWorld::CreateBattleUpdateThread(void* arg)
{
	GameWorld* instance = (GameWorld*)arg;
	instance->DoBattleUpdate();
}

void GameWorld::StartUpdate() {
	updateThread = std::unique_ptr<std::thread>(new std::thread(&CreateUpdateThread, this));
	saveThread = std::unique_ptr<std::thread>(new std::thread(&CreateSaveThread, this));
	battleUpdateThread = std::unique_ptr<std::thread>(new std::thread(&CreateBattleUpdateThread, this));
}

/**
* Saves game world on interval
*/
void GameWorld::DoSave() {
	using namespace std::chrono_literals;

	while (GameWorld::running) {

		std::cout << "Saving player list" << std::endl;
		memento->SetState();
		std::this_thread::sleep_for(5min);

	}

}

void GameWorld::DoBattleUpdate()
{
	using namespace std::chrono_literals;

	while (GameWorld::running) {

		//std::cout << "Updating game world." << std::endl;
		// Respawn room items
		if (battles_.get()) {
			battles_->Update();
		}
		std::this_thread::sleep_for(3s);

	}
}

/**
* Updates game world on interval
*/
void GameWorld::DoUpdate() {
	using namespace std::chrono_literals;

	while (GameWorld::running) {

		//std::cout << "Updating game world." << std::endl;
		// Respawn room items
		if (rooms_.get()) {
			std::vector<GameEntity*> rooms = rooms_->GetEntityVector();
			for (GameEntity* r : rooms) {
				//std::cout << "Respawning items in." << r->GetName() << std::endl;
				((Room*)r)->RespawnItems();
				((Room*)r)->RespawnMobs();
			}

		}
		std::this_thread::sleep_for(10s);

	}
}

Server& GameWorld::GetParent() const {
	return parent;
}

EntityList & GameWorld::GetRooms() const
{
	return *(rooms_.get());
}

EntityList & GameWorld::GetPlayers() const
{
	return *(players_.get());
}

EntityList& GameWorld::GetItems() const {
	return *items_;
}

EntityList & GameWorld::GetMobs() const
{
	return *(mobs_.get());
}

EntityList& GameWorld::GetMasterItems() const {
	return *master_items_;
}

EntityList & GameWorld::GetMasterMobs() const
{
	return *(master_mobs_.get());
}

BattleList & GameWorld::GetBattles() const
{
	return *(battles_.get());
}

CharacterClassList & GameWorld::GetCharacterClasses() const
{
	return *(character_classes_.get());
}

void GameWorld::ReleaseThreads() {
	GameWorld::running = false;
	//updateThread.get()->join();
	updateThread.release();
	saveThread.release();
	battleUpdateThread.release();

}