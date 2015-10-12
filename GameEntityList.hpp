#ifndef __GAMEENTITYLIST_H__
#define __GAMEENTITYLIST_H__

#include "GameEntity.hpp"

#include <map>

class GameEntityList {

private:
    std::map<int, GameEntity*> Map;

public:
    GameEntityList();
    ~GameEntityList();

    void AddGameEntity(GameEntity*);
    void RemoveGameEntity(int);
    GameEntity *GetGameEntity(int);
    int GetGameEntityCount();
};

#endif // __GAMEENTITYLIST_H__
