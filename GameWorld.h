#ifndef __GAMEWORLD_H__
#define __GAMEWORLD_H__

#include "EntityList.h"
#include "Player.h"
#include "Room.h"
#include "Item.h"

#include <map>

class GameWorld {

private:
    EntityList* rooms_;
    EntityList* players_;

public:
    GameWorld(  );
    ~GameWorld(  );

    void AddRoom( Room* entity );
    void AddPlayer( Player* entity );

    void RemoveRoom( int id );
    void RemovePlayer( int id );

	GameEntity *GetRoom( int id );
    GameEntity *GetPlayer( int id );

};

#endif // __GAMEWORLD_H__
