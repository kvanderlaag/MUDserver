#include "FileParser.h"

std::vector<std::string>* FileParser::ParseFile(std::string filename) {
	std::vector<std::string>* lines = new std::vector<std::string>();

	std::ifstream file(filename);

	std::string line;

	while (std::getline(file, line)) {
		lines->push_back(line);
	}

	return lines;
}

std::vector<std::string>* FileParser::ParseTsv(std::string tsv) {
	std::vector<std::string>* values = new std::vector<std::string>();

	std::istringstream csv_stream(tsv);
	std::string token;

	while (std::getline(csv_stream, token, '\t')) {     // '\n' is the default delimiter
		values->push_back(token);
	}

	return values;
}

std::vector<std::string>* FileParser::ParseCsv(std::string csv) {
	std::vector<std::string>* values = new std::vector<std::string>();

	std::istringstream csv_stream(csv);
	std::string token;

	while (std::getline(csv_stream, token, ',')) {     // '\n' is the default delimiter
		values->push_back(token);
	}

	if (!values->empty())
		return values;
	else
		return nullptr;
}

void FileParser::WritePlayers(std::string filename, std::vector<GameEntity*>* players) {
	std::ofstream file(filename);
	
	for each (Player* p in *players) {
		file << p->GetName() + "\t" + p->GetPassword() + "\n";
	}
}