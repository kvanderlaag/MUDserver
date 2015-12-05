#pragma once

#include <map>
#include <memory>
#include <string>

class CharacterClass {
private:
	std::string class_name_;
	std::map<std::string, int> levelup_increase_;

public:
	CharacterClass(std::string name);
	CharacterClass(std::string name, std::map<std::string, int> levelup_stat_increase_);
	~CharacterClass();

	std::map<std::string, int>& GenerateStats(int level);
	std::map<std::string, int>& LevelUpIncrease(int level);
};