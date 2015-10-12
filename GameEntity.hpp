#ifndef __GAMEENTITY_H__
#define __GAMEENTITY_H__

#include <string>

class GameEntity {

private:
    int index;
    std::string value;

public:
    GameEntity();
    GameEntity(int, std::string);
    ~GameEntity();
    
};

#endif // __GAMEENTITY_H__
