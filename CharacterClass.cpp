#include "CharacterClass.h"

CharacterClass::CharacterClass(int id,std::string name, GameWorld * parent) :
	id_(id),
	name_(name),
	parent_(*parent)
{

}

CharacterClass::CharacterClass(int id, std::string name, int health, int mana, int strength, int dexterity, int constitution, int intelligence, int charisma, GameWorld * parent) :
	id_(id),
	name_(name),
	health_(health),
	mana_(mana),
	strength_(strength),
	dexterity_(dexterity),
	constitution_(constitution),
	intelligence_(intelligence),
	charisma_(charisma),
	parent_(*parent)
{

}

CharacterClass::~CharacterClass() {

}

int CharacterClass::GetId()
{
	return id_;
}

GameWorld & CharacterClass::GetParent()
{
	return parent_;
}

void CharacterClass::SetName(std::string name)
{
	name_ = name;
}

void CharacterClass::SetHealth(int health)
{
	health_ = health;
}

void CharacterClass::SetMana(int mana)
{
	mana_ = mana;
}

void CharacterClass::SetStrength(int strength)
{
	strength_ = strength;
}

void CharacterClass::SetDexterity(int dexterity)
{
	dexterity_ = dexterity;
}

void CharacterClass::SetConstitution(int constitution)
{
	constitution_ = constitution;
}

void CharacterClass::SetIntelligence(int intelligence)
{
	intelligence_ = intelligence;
}

void CharacterClass::SetCharisma(int charisma)
{
	charisma_ = charisma;
}

std::string CharacterClass::GetName()
{
	return name_;
}

int CharacterClass::GetHealth()
{
	return health_;
}

int CharacterClass::GetMana()
{
	return mana_;
}

int CharacterClass::GetStrength()
{
	return strength_;
}

int CharacterClass::GetDexterity()
{
	return dexterity_;
}

int CharacterClass::GetConstitution()
{
	return constitution_;
}

int CharacterClass::GetIntelligence()
{
	return intelligence_;
}

int CharacterClass::GetCharisma()
{
	return charisma_;
}

PlayerStats & CharacterClass::GenerateStats(int level) {
	PlayerStats& stats = PlayerStats(0,0,0,0,0,0,0);

	for (std::size_t i = 0; i < level; i++) {
		 LevelUp(stats);
	}

	return stats;
}

void CharacterClass::LevelUp(PlayerStats & stats) {

	int mHealth = stats.GetMaxHealth();
	int mMana = stats.GetMaxMana();
	int mStrength = stats.GetMaxStrength();
	int mDexterity = stats.GetMaxDexterity();
	int mConstitution = stats.GetMaxConstitution();
	int mIntelligence = stats.GetMaxIntelligence();
	int mCharisma = stats.GetMaxCharisma();

	int nHealth = mHealth + health_;
	int nMana = mMana + mana_;
	int nStrength = mStrength + strength_;
	int nDexterity = mDexterity + dexterity_;
	int nConstitution = mConstitution + constitution_;
	int nIntelligence = mIntelligence + intelligence_;
	int nCharisma = mCharisma + charisma_;

	stats.SetMaxHealth(nHealth);
	stats.SetMaxMana(nMana);
	stats.SetMaxStrength(nStrength);
	stats.SetMaxDexterity(nDexterity);
	stats.SetMaxConstitution(nConstitution);
	stats.SetMaxIntelligence(nIntelligence);
	stats.SetMaxCharisma(nCharisma);
}