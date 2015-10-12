#include "GameEntityList.hpp"

#include <iostream>

GameEntityList::GameEntityList() {
    std::cout << "Created a map..." << std::endl;

}

GameEntityList::~GameEntityList() {
    std::cout << "Destroyed a map..." << std::endl;
}

void GameEntityList::AddGameEntity( GameEntity *entity ) {
    int index = Map.size();


    if( Map.find(index) != Map.end() ){
        std::cout << "Duplicate Key!!!" << std::endl;
    }

    Map.insert( std::pair<int,GameEntity*>(index, entity) );
}

GameEntity* GameEntityList::GetGameEntity( int index ) {
    if( !Map.empty() ) {
        return Map.find(index)->second;
    }
    return NULL;
}

void GameEntityList::RemoveGameEntity( int index ) {
    if( !Map.empty() ) {
        if( Map.find(index) != Map.end() )
            Map.erase(index);
        else
            std::cout << "Could not find the GameEntity to remove!!! ";
    }
}

int GameEntityList::GetGameEntityCount(  ) {
    return Map.size();
}
