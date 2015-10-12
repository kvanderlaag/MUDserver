#include "GameEntity.hpp"

#include <iostream>

GameEntity::GameEntity(  ) {
    std::cout << "Created an entity..." << std::endl;
}

GameEntity::GameEntity( int id, std::string val ) {
    index = id;
    value = val;
    std::cout << "Created an entity..." << std::endl;
}

GameEntity::~GameEntity() {
    std::cout << "Destroyed an entity..." << std::endl;
}
