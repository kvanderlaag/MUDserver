#include "EntityList.h"

#include <iostream>

EntityList::EntityList() {						/*Create an entity list*/
    std::cout << "Created a list..." << std::endl;
}

EntityList::~EntityList() {						/*Delete an entity list*/
    std::cout << "Destroyed a list..." << std::endl;
}

void EntityList::AddEntity(GameEntity *game_entity) {			/*Add a game entity to an existing list*/

	if( map_.find( game_entity->GetId() ) != map_.end() ){
        std::cout << "Duplicate id!!!" << std::endl;
    }

    map_.insert( std::pair<int,GameEntity*>( game_entity->GetId(), game_entity ) );
}

GameEntity* EntityList::GetEntity(int id) {				/*Get the entity corresponding to an ID*/
    if( !map_.empty() ) {
        return map_.find( id )->second;
    }
    return NULL;
}

void EntityList::RemoveEntity(int id) {					/*Remove an entity corresponding to an ID*/
    if( !map_.empty() ) {
        if( map_.find(id) != map_.end() )
            map_.erase(id);
        else
            std::cout << "Could not find the GameEntity to remove!!! ";
    }
}

int EntityList::GetEntityCount() {					/*Return how many entities are in the list*/
    return map_.size();
}
