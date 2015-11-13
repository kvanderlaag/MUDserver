#include "GameWorld.h"

#include <iostream>

GameWorld::GameWorld(  ) {
    std::cout << "Created a world..." << std::endl;
}

GameWorld::~GameWorld(  ) {
    std::cout << "Destroyed a world..." << std::endl;
}

void GameWorld::AddRoom( GameEntity *room ) {
    rooms_->AddEntity( room );
}

void GameWorld::AddPlayer( GameEntity *player ) {
    players_->AddEntity( player );
}

void GameWorld::RemoveRoom( int id ) {
    rooms_->RemoveEntity( id );
}

void GameWorld::RemovePlayer( int id ) {
    players_->RemoveEntity( id );
}

GameEntity* GameWorld::GetRoom( int id ) {
    return rooms_->GetEntity( id );
}

GameEntity* GameWorld::GetPlayer( int id ) {
    return players_->GetEntity( id );
}
