#include "Room.h"

/**
 * Create a new room with an id and name
 * Room inherits GameEntity
 */
Room::Room(int id, std::string name, GameWorld* world) :
	GameEntity(id, name, world),
	exits_(new EntityList()),
	items_(new EntityList()),
	players_(new EntityList())
{
	std::cout << "Created a room..." << std::endl;
}

/** Create a new room with an id, name, and description */
Room::Room(int id, std::string name, std::string description, GameWorld* world) :
	GameEntity(id, name, description, world),
	exits_(new EntityList()),
	items_(new EntityList()),
	players_(new EntityList())
{
	//std::cout << "Created a room..." << std::endl;
}

/** Remove a room */
Room::~Room(  )
{
	std::cout << "Destroyed a room..." << std::endl;
}

/**
 * Each room will have a list of exits (denotes which rooms can be accessed from that room)
 * This function will add an exit to the existing exit list of a room
 */
void Room::AddExit(GameEntity& roomexit)
{
	exits_->AddEntity(roomexit);
}

/**
 * Each room will have a list of items (denotes what items are available to be picked up by characters in the room)
 * This function will add an item to the existing item list of a room
 */
void Room::AddItem(GameEntity& item)
{
	items_->AddEntity(item);
}

void Room::AddMasterItem(int id) {
	original_items_.push_back(id);
}

void Room::SpawnItem(int masterId) {
	Item& copyFrom = (Item&) *(GetWorld().GetMasterItems().GetEntity(masterId));
	Item* spawnItem = new Item(GetWorld().GetItems().GetNextId(), copyFrom);

	GetWorld().GetItems().AddEntity(*spawnItem);
	AddItem(*spawnItem);
	//std::cout << "Spawning " << spawnItem->GetName() << " in " << GetName() << " (Master ID: " << spawnItem->GetMasterId() << ")" << std::endl;

	std::ostringstream outString;
	outString << "\n" << cGreen << spawnItem->GetName() << cDefault << " pops into existence.\n";

	std::vector<GameEntity*> roomPlayers = players_->GetEntityVector();
	for (GameEntity* p : roomPlayers) {
		Message* msg = new Message(outString.str(), ((Player*) p)->GetConnectionId(), Message::outputMessage);
		GetWorld().GetParent().PutMessage(msg);
	}
}

/**
 * Each room will have a list of players (denotes what players are currently in the room at the time)
 * This function will add a player to the existing player list of a room
 * Players get added to the player list when the enter a room
 */
void Room::AddPlayer(GameEntity& player)
{
	players_->AddEntity(player);
}

/**
 * Remove an exit from the existing exit list of a room
 */
void Room::RemoveExit(int id)
{
    exits_->RemoveEntity(id);
}

/**
 * Remove an item from the existing item list of a room
 * Items are removed when a player picks up/takes an item
 */
void Room::RemoveItem(int id)
{
	items_->RemoveEntity(id);
}

/**
 * Remove a player from the existing player list of a room
 * Players are removed when they leave a roome
 */
void Room::RemovePlayer(int id)
{
	players_->RemoveEntity(id);
}

/**
 * Functions as a check made to see if a certain room exists in a room's exit list (using a room id)
 * Return the GameEntity(id) if it is found in the exit list, else return null if it is not
 */
GameEntity* Room::GetExit(std::string exit)
{
	if (exit == "e")
		exit = "east";
	else if (exit == "w")
		exit = "west";
	else if (exit == "n")
		exit = "north";
	else if (exit == "s")
		exit = "south";
	std::map<int, std::string>::iterator it = directions_.begin();
	for (it; it != directions_.end(); it++) {
		if (it->second == exit) {
			return exits_->GetEntity(it->first);
		}
	}
	return nullptr;
}

/**
 * Gets an item GameEntity using an id if it's in the item list.
 * Return the GameEntity(id) if it is found in the item list, else return null if it is not
 */
GameEntity* Room::GetItem(int id)
{
	return items_->GetEntity(id);
}

/**
 * Gets a player GameEntity using an id if it's in the player list.
 * Return the GameEntity(id) if it is found in the player list, else return null if it is not
 */
GameEntity* Room::GetPlayer(int id)
{
	return players_->GetEntity(id);
}

GameEntity* Room::FindExit(std::string name) const {
	GameEntity* exit = exits_->FindEntity(name);
	if (exit) {
		return exit;
	}
	return nullptr;
}


GameEntity* Room::FindItem(std::string name) const {
	std::vector<GameEntity*> items = items_->GetEntityVector();
	for (GameEntity* i : items) {
		std::string lowername = i->GetName();
		for (size_t j = 0; j < lowername.length(); ++j) {
			lowername.at(j) = std::tolower(lowername.at(j));
		}
		if (lowername == name || ((Item*) i)->FindShortName(name)) {
			return i;
		}
	}
	return nullptr;
}


GameEntity* Room::FindPlayer(std::string name) const {
	std::vector<GameEntity*> players = players_->GetEntityVector();

	std::string lowername(name);
	for (size_t i = 0; i < lowername.length(); ++i) {
		lowername.at(i) = std::tolower(lowername.at(i));
	}

	for (GameEntity* p : players) {
		std::string pName(p->GetName());
		for (size_t i = 0; i < pName.length(); ++i) {
			pName.at(i) = std::tolower(pName.at(i));
		}
		if (pName == lowername) {
			return p;
		}
	}
	return nullptr;
}


/**
* Looks through all the lists ands finds the entity with the matching name
* TODO this is slooow, make a map with name -> entity
*/
GameEntity* Room::FindEntity(std::string name) const
{
	GameEntity* esearch = exits_->FindEntity(name);
	if (esearch)
	{
		return esearch;
	}

	GameEntity* isearch = items_->FindEntity(name);
	if (isearch)
	{
		return isearch;
	}

	GameEntity* psearch = players_->FindEntity(name);
	if (psearch)
	{
		return psearch;
	}

	return nullptr;
}

std::vector<GameEntity*> Room::GetPlayerVector()
{
	return players_->GetEntityVector();
}

std::vector<GameEntity*> Room::GetItemVector()
{
	return items_->GetEntityVector();
}

std::map<int, std::string> Room::GetExitVector()
{
	return std::map<int, std::string>(directions_);
}

void Room::AddDirection(int id, std::string dir) {
	directions_.insert(std::pair<int, std::string>(id, dir));
}

void Room::RespawnItems() {
	std::vector<Item*> currentItems = (std::vector<Item*>&) items_->GetEntityVector();
	std::map<int, int> items_to_add;
	for (int i : original_items_) {
		items_to_add.insert(std::pair<int, int>(i, i));

	}

	for (Item* i : currentItems) {
		items_to_add.erase(i->GetMasterId());
	}

	for (std::pair<int, int> i : items_to_add) {
		SpawnItem(i.second);
	}
}