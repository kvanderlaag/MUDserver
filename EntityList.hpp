#ifndef __ENTITYLIST_H__
#define __ENTITYLIST_H__

#include "GameEntity.hpp"

#include <map>

class EntityList {

private:
    std::map<int, GameEntity*> map_;

public:
    EntityList(  );
    ~EntityList(  );

    void AddEntity( GameEntity* game_entity );
    void RemoveEntity( int id );
    GameEntity *GetEntity( int id );
    int GetEntityCount(  );

};

#endif // ____ENTITYLIST_H__
