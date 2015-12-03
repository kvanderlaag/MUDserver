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

void FileParser::WritePlayers(std::string filename, std::vector<GameEntity*> players) {
	std::ofstream file(filename);
	
	for (GameEntity* e : players) {
		Player* p = (Player*) e;
		std::stringstream playerOut;
		playerOut << p->GetName() << "\t";
		playerOut << p->GetPassword() << "\t";
		playerOut << p->GetRoomId() << "\t";

		playerOut << p->GetStats().GetMaxHealth() << ",";
		playerOut << p->GetStats().GetMaxMana() << ",";
		playerOut << p->GetStats().GetMaxStrength() << ",";
		playerOut << p->GetStats().GetMaxDexterity() << ",";
		playerOut << p->GetStats().GetMaxConstitution() << ",";
		playerOut << p->GetStats().GetMaxIntelligence() << ",";
		playerOut << p->GetStats().GetMaxCharisma() << "";

		playerOut << "\t";

		playerOut << p->GetDescription();
		
		playerOut << "\t";

		std::vector<GameEntity*> inventory = p->GetItemVector();
		if (!inventory.empty()) {
			if (inventory.size() == 1) {
				playerOut << ((Item*)inventory.at(0))->GetMasterId();
			}
			else {
				for (size_t i = 0; i < inventory.size() - 2; ++i) {
					playerOut << ((Item*)inventory.at(i))->GetMasterId() << ",";
				}
				playerOut << ((Item*)inventory.at(inventory.size() - 1))->GetMasterId();
			}
			
		}
		

		playerOut << "\n";

		file << playerOut.str();
	}
}
