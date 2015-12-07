#include "CharacterClassList.h"


CharacterClassList::CharacterClassList(GameWorld * world) :
	parent_(*world)
{
	next_ids_.push_back(0);
}

CharacterClassList::~CharacterClassList()
{
}

int CharacterClassList::GetNextId()
{
	int id = next_ids_.back();

	next_ids_.pop_back();

	// if its empty, push id+1 onto it
	if (next_ids_.size() == 0)
	{
		next_ids_.push_back(id + 1);
	}

	return id;
}

void CharacterClassList::PutNextId(int nextId)
{
	next_ids_.push_back(nextId);
}

void CharacterClassList::AddCharacterClass(CharacterClass * c)
{
	character_classes_.insert(std::pair<int, CharacterClass*>(c->GetId(), c));
}

void CharacterClassList::DeleteCharacterClass(CharacterClass * c)
{
	character_classes_.erase(c->GetId());
}

void CharacterClassList::DeleteCharacterClass(int id)
{
	character_classes_.erase(id);
}

CharacterClass * CharacterClassList::GetCharacterClassByName(std::string name)
{
	for (std::pair<int, CharacterClass*> pair : character_classes_) {
		CharacterClass* c = pair.second;
		if (name == c->GetName()) {
			return c;
		}
	}
	return nullptr;
}

CharacterClass * CharacterClassList::GetCharacterClassById(int id)
{
	for (std::pair<int, CharacterClass*> pair : character_classes_) {
		CharacterClass* c = pair.second;
		if (id == c->GetId()) {
			return c;
		}
	}
	return nullptr;
}

GameWorld & CharacterClassList::GetParent() const
{
	return parent_;
	// TODO: insert return statement here
}
