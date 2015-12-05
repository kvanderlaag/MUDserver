#include "CharacterClass.h"

CharacterClass::CharacterClass(std::string name) {

}

CharacterClass::CharacterClass(std::string name, std::map<std::string, int> levelup_increase) {

}

CharacterClass::~CharacterClass() {

}

std::map<std::string. int>& CharacterClass::GenerateStats(int level) {
	std::map<std::string, int>& stats;

	stats["strength"] = 0;
	stats["dexterity"] = 0;
	stats["constitution"] = 0;
	stats["intelligence"] = 0;
	stats["wisdom"] = 0;
	stats["charisma"] = 0;


	for (size_t i = 0; i < level; i++) {
		std::map<std::string, int>& increase = LevelUpIncrease(i);
		stats["strength"]		+= increase["strength"];
		stats["dexterity"]		+= increase["dexterity"];
		stats["constitution"]	+= increase["constitution"];
		stats["intelligence"]	+= increase["intelligence"];
		stats["wisdom"]			+= increase["wisdom"];
		stats["charisma"]		+= increase["charisma"];
	}

	return stats
}

std::map<std::string, int>& CharacterClass::LevelUpIncrease(int level) {
	std::map<std::string, int>& increase;

	increase["strength"]		= levelup_increase_["strength"];
	increase["dexterity"]		= levelup_increase_["dexterity"];
	increase["constitution"]	= levelup_increase_["constitution"];
	increase["intelligence"]	= levelup_increase_["intelligence"];
	increase["wisdom"]			= levelup_increase_["wisdom"];
	increase["charisma"]		= levelup_increase_["charisma"];

	return increase;
}