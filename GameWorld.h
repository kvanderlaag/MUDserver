#ifndef __GAMEWORLD_H__
#define __GAMEWORLD_H__

#include "EntityList.h"
#include "ConnectionList.h"
#include "Player.h"
#include "Room.h"
#include "Item.h"
#include "Message.h"

#include <map>
#include <vector>

class GameWorld {

private:
    EntityList* rooms_; // room_id/room_object
    EntityList* players_; // player_id/player_object
	ConnectionList* current_players_; // connection_id/player_id

public:
    GameWorld();
    ~GameWorld();

    void AddRoom(Room* entity);
    void AddPlayer(Player* entity);

    void RemoveRoom(int id);
    void RemovePlayer(int id);

	GameEntity *GetRoom(int id);
    GameEntity *GetPlayer(int id);

	std::vector<Message> *Look(int connection_id);
	std::vector<Message> *Look(int connection_id, std::string entity);
	std::vector<Message> *Move(int connection_id, std::string exit);
	std::vector<Message> *Say(int connection_id, std::string words);
    
    std::vector<Message> *SignUp(int connection_id, std::string login_name, std::string password);

};

#endif // __GAMEWORLD_H__
