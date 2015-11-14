#include "Player.h"

Player::Player( int id, std::string name ) : GameEntity(id, name){
    std::cout << "Created a player..." << std::endl;
}

Player::Player(  int id, std::string name, int password ) : GameEntity( id, name ) {
    password_ = password;
    std::cout << "Created a player with connection ID & password..." << std::endl;
}

Player::~Player() {
    std::cout << "Removed a player..." << std::endl;
}

void Player::AssignConnectionID(int* newConnectionID){
    *connectionID_ = *newConnectionID;
}

int* Player::GetConnectionID() {
    return connectionID_;
}

int Player::GetPassword() {
    return password_;
}

int* Player::GetRoomID(){
    return roomID_;
}

void Player::ChangeRoomID(int* newRoomID){
    *roomID_ = *newRoomID;
}

void Player::PrintPlayer(){
    Print();
    std::cout << connectionID_ << "is currently located at room:" << roomID_ << std::endl;
}

bool Player::CheckPassword(int inputPassword) {
	if(inputPassword == password_){
        return true;
        std::cout << "Password is correct..." << std::endl;
    }
    return false;
    std::cout << "Incorrect password..." << std::endl; 
}

void Player::AddItem(GameEntity *item) {
	items_->AddEntity(item);
}

void Player::RemoveItem(int id) {
	items_->RemoveEntity(id);
}

GameEntity* Player::GetItem(int id) {
	return items_->GetEntity(id);
}