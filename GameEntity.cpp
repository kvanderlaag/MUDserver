#include "GameEntity.h"

#include <iostream>

GameEntity::GameEntity(int id, std::string name) {				/*Create a game entity*/
    id_ = id;
    name_ = name;
    description_ = "";

    std::cout << "Created an entity..." << std::endl;
}

GameEntity::GameEntity(int id, std::string name, std::string description) {	/*Creates a game entity with a description*/
    id_ = id;
    name_ = name;
    description_ = description;

    std::cout << "Created an entity..." << std::endl;
}

GameEntity::~GameEntity() {							/*Remove an entity*/
    std::cout << "Destroyed an entity..." << std::endl;
}

int GameEntity::GetId() {							/*Get the Id of an entity*/
    return id_;
}

std::string GameEntity::GetName() {						/*Get the name of an entity*/
	return name_;
}

std::string GameEntity::GetDescription() {					/*Get the description of an entity*/
    return description_;
}

void GameEntity::SetDescription(std::string description) {			/*Change or set the description of an entity*/
    description_ = description;
}

void GameEntity::Print() {							/*Print the ID, name, and description of an entity*/
    std::cout << id_ << " " << name_ << " " << description_ << std::endl;
}
