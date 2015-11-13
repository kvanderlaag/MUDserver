#include "Player.h"

Player::Player( int id, std::string name ) : GameEntity(id, name){
    std::cout << "Created a player..." << std::endl;
}

Player::Player(  int id, std::string name, int connectionID ) : GameEntity( id, name ) {
    connectionID_ = connectionID;
    std::cout << "Created a player with connection ID..." << std::endl;
}

Player::~Player() {
    std::cout << "Removed a player..." << std::endl;
}

int Player::GetConnectionID() {
    return connectionID_;
}

void Player::PrintPlayer(){
	Print();
    std::cout << connectionID_ << std::endl;
}
