#ifndef __FILEPARSER_H__
#define __FILEPARSER_H__

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Player.h"

/*Header file for FileParser*/
class FileParser
{

private:

								
public:
	static std::vector<std::string>* ParseFile(std::string filename);
	static std::vector<std::string>* ParseTsv(std::string tsv);
	static std::vector<std::string>* ParseCsv(std::string csv);
	static void WritePlayers(std::string filename, std::vector<GameEntity*>* players);
};

#endif // __FILEPARSER_H__
