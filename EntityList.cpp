/*EntityList.cpp implements the header file EntityList.h
*/
#include "EntityList.h"

#include <iostream>

/*Default constructor that creates an entity list then prints out the information*/
EntityList::EntityList() {	
    std::cout << "Created a list..." << std::endl;
}

/*Destructor that delete an entity list then prints out the information*/
EntityList::~EntityList() {	
    std::cout << "Destroyed a list..." << std::endl;
}

/*Takes the pointer of a game entity and adds the game entity to an existing list.
 *It returns warning if the passed IDs are duplicated.
*/
void EntityList::AddEntity(GameEntity *game_entity) {			

	if( map_.find( game_entity->GetId() ) != map_.end() ){
        std::cout << "Duplicate id!!!" << std::endl;
    }

    map_.insert( std::pair<int,GameEntity*>( game_entity->GetId(), game_entity ) );
}

/*Get the entity corresponding to an ID*/
GameEntity* EntityList::GetEntity(int id) {	
    if( !map_.empty() ) {
        return map_.find( id )->second;
    }
    return NULL;
}

/*Remove an entity corresponding to an ID*/
void EntityList::RemoveEntity(int id) {	
    if( !map_.empty() ) {
        if( map_.find(id) != map_.end() )
            map_.erase(id);
        else
            std::cout << "Could not find the GameEntity to remove!!! ";
    }
}

/*Return how many entities are in the list*/
int EntityList::GetEntityCount() {	
    return map_.size();
}
