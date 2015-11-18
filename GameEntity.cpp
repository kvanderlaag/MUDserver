/*GameEntity.cpp implements the header file GameEntity.h*/
#include "GameEntity.h"

#include <iostream>

/*Default constructor that creates a game entity by setting a permanent ID, name, and a blank description. */
GameEntity::GameEntity(int id, std::string name) {
    id_ = id;
    name_ = name;
    description_ = "";

    std::cout << "Created an entity..." << std::endl;
}

/*A standard constructor that creates a game entity with a description*/
GameEntity::GameEntity(int id, std::string name, std::string description) {
    id_ = id;
    name_ = name;
    description_ = description;

    std::cout << "Created an entity..." << std::endl;
}

/*A destructor that removes an entity*/
GameEntity::~GameEntity() {
    std::cout << "Destroyed an entity..." << std::endl;
}

/*Get the Id of an entity*/
int GameEntity::GetId() {
    return id_;
}

/*Get the name of an entity*/
std::string GameEntity::GetName() {
	return name_;
}

/*Get the description of an entity*/
std::string GameEntity::GetDescription() {
    return description_;
}

/*Change or set the description of an entity*/
void GameEntity::SetDescription(std::string description) {
    description_ = description;
}

/*Print the ID, name, and description of an entity*/
void GameEntity::Print() {
    std::cout << id_ << " " << name_ << " " << description_ << std::endl;
}
