#ifndef __ENTITYLIST_H__
#define __ENTITYLIST_H__

#include "GameEntity.h"

#include <map>

class EntityList {

private:
    std::map<int, GameEntity*> map_;

public:
    EntityList();
    ~EntityList();

    void AddEntity(GameEntity* game_entity);
    void RemoveEntity(int id);
    GameEntity *GetEntity( int id);
    int GetEntityCount();

};

#endif // __ENTITYLIST_H__
