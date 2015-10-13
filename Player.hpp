#include <iostream>
#include "GameEntity.hpp"

class Player: public GameEntity{

private:
    int connectionID;

public:
    Player( int id, std::string name);
	Player( int id, std::string name, int connectionID);
    ~Player(  );
	void PrintPlayer(  ) ;

	std::string GetName(  );
	int GetConnectionID;

};

#endif 
