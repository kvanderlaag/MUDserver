#ifndef __GAMEWORLD_H__
#define __GAMEWORLD_H__

#include "EntityList.hpp"
#include "GameEntity.hpp"

#include <map>

class GameWorld {

private:
    EntityList* rooms_;
    EntityList* players_;

public:
    GameWorld(  );
    ~GameWorld(  );

    void AddRoom( GameEntity* entity );
    void AddPlayer( GameEntity* entity );

    void RemoveRoom( int id );
    void RemovePlayer( int id );

    GameEntity *GetRoom( int id );
    GameEntity *GetPlayer( int id );

};

#endif // __GAMEWORLD_H__
