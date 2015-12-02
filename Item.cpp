/** Item.cpp implements the header file Item.h*/
#include "Item.h"

/**Create an item with ID and a description*/
Item::Item(int id, std::string description, GameWorld* world, int master) : GameEntity(id, description, world),
	masterId(master)
{
#ifdef _DEBUG_FLAG
	std::cout <<"Created an item..." << std::endl;
#endif
}

/**Create an item with an ID, a name and description*/
Item::Item(int id, std::string name, std::string description, GameWorld* world, int master) : GameEntity(id, name, description, world),
	masterId(master)
{
#ifdef _DEBUG_FLAG
	std::cout << "Created an item..." << std::endl;
#endif
}

/**Create an item with an ID and another item to copy from */
Item::Item(int newId, const Item& other) : GameEntity(newId, other.GetName(), other.GetDescription(), &(other.GetWorld())),
	mShortNames(other.GetShortNameVector()),
	masterId(other.GetMasterId())
{
}

void Item::AddShortName(std::string name) {
	if (!name.empty()) {
		for (std::string shortname : mShortNames) {
			if (shortname == name)
				return;
		}
		mShortNames.push_back(name);
	}
}

std::vector<std::string> Item::GetShortNameVector() const {
	return mShortNames;
}

bool Item::FindShortName(std::string shortName) const {
	if (!shortName.empty()) {
		for (std::string s : mShortNames) {
			if (s == shortName)
				return true;
		}
	}
	return false;
}

int Item::GetMasterId() const {
	return masterId;
}

/**A destructor that destorys an item*/
Item::~Item()
{
	std::cout << "Destroyed an item..." << std::endl;
}
