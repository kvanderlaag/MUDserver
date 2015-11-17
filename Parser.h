#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include <vector>

#include "GameWorld.h"

class Parser {

private:

public:
	std::vector<Message*>* Parse(GameWorld* world, int connection_id, std::string str);

};

#endif // __PARSER_H__