#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include <vector>

#include "GameWorld.h"

/**
* Header file for parser
*/
class Parser
{

private:

public:
	Message* Parse(const Message* mess) const;

};

#endif // __PARSER_H__
