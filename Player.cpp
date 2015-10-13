#include "Player.hpp"

Player::Player( int id, std::string name ) : GameEntity(id, name){
    std::cout << "Created a player..." << std::endl;
}

Player::Player(  int id, std::string name, int connectionID) : GameEntity( id, name);{
    connectionID_ = connectionID;
    std::cout << "Added a player with connection ID..." << std::endl;
}

Player::~Player(  ) : ~GameEntity(  ){
    std::cout << "Removed a player..." << std::endl;
}

int Player::GetConnectionId(  ) {
    return connectionID;
}

std::string Player::GetName(  ) {
    return name;
}

void Player::PrintPlayer(  ) : Print(){
    std::cout << id << " " << name << " " << connectionID << std::endl;
}
