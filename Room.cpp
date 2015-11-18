#include "Room.h"

/**
 * Create a new room with an id and name
 * Room inherits GameEntity
 */
Room::Room(int id, std::string name) : GameEntity(id, name) {
	std::cout << "Created a room..." << std::endl;
}

/** Create a new room with an id, name, and description */
Room::Room(int id, std::string name, std::string description) : GameEntity(id, name, description) {
	std::cout << "Created a room..." << std::endl;
}

/** Remove a room */
Room::~Room(  ) {
	std::cout << "Destroyed a room..." << std::endl;
}

/**
 * Each room will have a list of exits (denotes which rooms can be accessed from that room)
 * This function will add an exit to the existing exit list of a room
 */
void Room::AddExit(GameEntity *roomexit) {
	exits_->AddEntity(roomexit);
}

/**
 * Each room will have a list of items (denotes what items are available to be picked up by characters in the room)
 * This function will add an item to the existing item list of a room
 */
void Room::AddItem(GameEntity *item) {
	items_->AddEntity(item);
}

/**
 * Each room will have a list of players (denotes what players are currently in the room at the time)
 * This function will add a player to the existing player list of a room
 * Players get added to the player list when the enter a room
 */
void Room::AddPlayer(GameEntity *player) {
	players_->AddEntity(player);
}

/**
 * Remove an exit from the existing exit list of a room
 */
void Room::RemoveExit(int id) {
    exits_->RemoveEntity(id);
}

/**
 * Remove an item from the existing item list of a room
 * Items are removed when a player picks up/takes an item
 */
void Room::RemoveItem(int id) {
	items_->RemoveEntity(id);
}

/**
 * Remove a player from the existing player list of a room
 * Players are removed when they leave a roome
 */
void Room::RemovePlayer(int id) {
	players_->RemoveEntity(id);
}

/**
 * Functions as a check made to see if a certain room exists in a room's exit list (using a room id)
 * Return the GameEntity(id) if it is found in the exit list, else return null if it is not
 */
GameEntity* Room::GetExit(int id) {
	return exits_->GetEntity(id);
}

/**
 * Gets an item GameEntity using an id if it's in the item list.
 * Return the GameEntity(id) if it is found in the item list, else return null if it is not
 */
GameEntity* Room::GetItem(int id) {
	return items_->GetEntity(id);
}

/**
 * Gets a player GameEntity using an id if it's in the player list.
 * Return the GameEntity(id) if it is found in the player list, else return null if it is not
 */
GameEntity* Room::GetPlayer(int id) {
	return players_->GetEntity(id);
}
