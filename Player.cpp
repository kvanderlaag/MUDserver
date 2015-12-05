/**
* Player.cpp is included by header file Player.h implementing the functionalities from Player.h
*/
#include "Player.h"


/**
* The default constructor create a naive object player by permanent player ID and initial name.
*/
Player::Player(int id, std::string name, GameWorld* world) : GameEntity(id, name, world),
	items_(new EntityList()),
	stats_(std::unique_ptr<PlayerStats>(new PlayerStats()))
{
	connection_id_ = -1;
	password_ = "";
	room_id_ = 0;

    std::cout << "Created a player..." << std::endl;
}

/**
* A standard constructor create an object player by permanent player ID, initial name, and password.
*/
Player::Player(int id, std::string name, std::string password, GameWorld* world) : GameEntity(id, name, world),
	items_(new EntityList()),
	stats_(std::unique_ptr<PlayerStats>(new PlayerStats()))
{
	connection_id_ = -1;
    password_ = password;
	room_id_ = 0;
#ifdef _DEBUG_FLAG
    std::cout << "Created a player with connection ID & password..." << std::endl;
#endif
}

/**
* The destructor ~Player() remove object player.
*/
Player::~Player() {
    std::cout << "Deleting player " << GetName() << std::endl;
}

/**
* The PrintPlayer function is called to print the basic information for the player. It prints out the current connection ID and the current room ID of the player.
*/
void Player::PrintPlayer() {
	Print();
	std::cout << connection_id_ << "is currently located at room:" << room_id_ << std::endl;
}

/**
* This function takes a pointer variable passed by the server and changes the current connection ID to the new connection ID.
*/
void Player::SetConnectionId(int new_connection_id) {
	connection_id_ = new_connection_id;
}

/**
* The GetConnectionID function returns the current connection ID.
*/
int Player::GetConnectionId() {
    return connection_id_;
}

/**
* The GetPassword function returns the initial passoword.
*/
std::string Player::GetPassword() const {
    return password_;
}

/**
* The ChangeRoomID function takes the pointer variable passed by the server and modifies the current player's room ID (i.e. room location) to the new room ID.
*/
void Player::SetRoomId(int room_id) {
	room_id_ = room_id;
}

/**
* The destructor ~Player() remove object player.
*/
int Player::GetRoomId(){
    return room_id_;
}

/**
* The function AddItem receives a pointer of type GameEntity and add item to the item list within player object.
*/
void Player::AddItem(GameEntity& item) {
	items_.get()->AddEntity(item);
}

/**
* The function RemoveItem receives the ID of an item and remove this item from the item list within player object.
*/
void Player::RemoveItem(int id) {
	items_->RemoveEntity(id);
}

/**
* The function RemoveItem receives the name of an item and remove this item from the item list within player object.
*/
void Player::RemoveItem(std::string name) {
	GameEntity& item = *(items_->FindEntity(name));
	items_->RemoveEntity(item.GetId());
}

/**
* The function GetItem receives the ID of an item and find the item to the item list within player object.
*/
GameEntity* Player::GetItem(int id) {
	return items_->GetEntity(id);
}

/**
* The function GetItemVector returns a vector containing pointers to the items in the current player's inventory.
*/
std::vector<GameEntity*> Player::GetItemVector() {
	std::vector<GameEntity*> inventory = items_->GetEntityVector();
	return inventory;
}

GameEntity* Player::FindItem(std::string name) const {
	std::vector<GameEntity*> inventory = items_->GetEntityVector();
	for (GameEntity* i : inventory) {
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

int Player::Damage(const int damage) {
	stats_->SetHealth(stats_->GetHealth() - damage);
	if (stats_->GetHealth() <= 0) {
		return 1;
	}
	return 0;
}

PlayerStats& Player::GetStats() {
	return *(stats_.get());
}

void Player::SetPassword(std::string password) {
	password_ = password;
}