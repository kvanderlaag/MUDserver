#include "PlayerStats.h"



PlayerStats::PlayerStats() : mHealth(iDefaultHealth), mMana(iDefaultMana), mTempMana(iDefaultMana),
	mTempHealth(iDefaultHealth), mStrength(iDefaultStrength), mTempStrength(iDefaultStrength), 
	mDexterity(iDefaultDexterity), mTempDexterity(iDefaultDexterity), mConstitution(iDefaultConstitution), 
	mTempConstitution(iDefaultConstitution), mIntelligence(iDefaultIntelligence), 
	mTempIntelligence(iDefaultIntelligence), mCharisma(iDefaultCharisma), mTempCharisma(iDefaultCharisma)
{
}

PlayerStats::PlayerStats(const int MaxHealth, const int MaxMana, const int MaxStrength,
	const int MaxDexterity, const int MaxConstitution, const int MaxIntelligence,
	const int MaxCharisma) : mHealth(MaxHealth), mTempHealth(MaxHealth), mMana(MaxMana), mTempMana(MaxMana),
	mStrength(MaxStrength), mTempStrength(MaxStrength), mDexterity(MaxDexterity),
	mTempDexterity(MaxDexterity), mConstitution(MaxConstitution), mTempConstitution(MaxConstitution),
	mIntelligence(MaxIntelligence), mTempIntelligence(MaxIntelligence), mCharisma(MaxCharisma),
	mTempCharisma(MaxCharisma)
{
}


PlayerStats::~PlayerStats()
{
}

/**
* Health functions
*/

const int PlayerStats::GetMaxHealth() const {
	return mHealth;
}

const int PlayerStats::GetHealth() const {
	return mTempHealth;
}

void PlayerStats::SetMaxHealth(const int newHealth) {
	mHealth = newHealth;
}

void PlayerStats::SetHealth(const int newHealth) {
	mTempHealth = newHealth;
}


/**
* Mana functions
*/

const int PlayerStats::GetMaxMana() const {
	return mMana;
}

const int PlayerStats::GetMana() const {
	return mTempMana;
}

void PlayerStats::SetMaxMana(const int newMana) {
	mMana = newMana;
}

void PlayerStats::SetMana(const int newMana) {
	mTempMana = newMana;
}


/**
* Strength functions
*/

const int PlayerStats::GetMaxStrength() const {
	return  mStrength;
}

const int PlayerStats::GetStrength() const {
	return mTempStrength;
}

void PlayerStats::SetMaxStrength(const int newStrength) {
	mStrength = newStrength;
}

void PlayerStats::SetStrength(const int newStrength) {
	mTempStrength = newStrength;
}


/**
* Dexterity functions
*/

const int PlayerStats::GetMaxDexterity() const {
	return mDexterity;
}

const int PlayerStats::GetDexterity() const {
	return mTempDexterity;
}

void PlayerStats::SetMaxDexterity(const int newDexterity) {
	mDexterity = newDexterity;
}

void PlayerStats::SetDexterity(const int newDexterity) {
	mTempDexterity = newDexterity;
}


/**
* Constitution functions
*/

const int PlayerStats::GetMaxConstitution() const {
	return mConstitution;
}

const int PlayerStats::GetConstitution() const {
	return mTempConstitution;
}

void PlayerStats::SetMaxConstitution(const int newConstitution) {
	mConstitution = newConstitution;
}

void PlayerStats::SetConstitution(const int newConstitution) {
	mTempConstitution = newConstitution;
}


/**
* Intelligence functions
*/

const int PlayerStats::GetMaxIntelligence() const {
	return mIntelligence;
}

const int PlayerStats::GetIntelligence() const {
	return mTempIntelligence;
}

void PlayerStats::SetMaxIntelligence(const int newIntelligence) {
	mIntelligence = newIntelligence;
}

void PlayerStats::SetIntelligence(const int newIntelligence) {
	mTempIntelligence = newIntelligence;
}


/**
* Charisma functions
*/

const int PlayerStats::GetMaxCharisma() const {
	return mCharisma;
}

const int PlayerStats::GetCharisma() const {
	return mTempCharisma;
}

void PlayerStats::SetMaxCharisma(const int newCharisma) {
	mCharisma = newCharisma;
}

void PlayerStats::SetCharisma(const int newCharisma) {
	mTempCharisma = newCharisma;
}

void PlayerStats::SetStats(const int hp, const int mp, const int str, const int dex, const int con, const int int_, const int cha) {
	mHealth = mTempHealth = hp;
	mMana = mTempMana = mp;
	mStrength = mTempStrength = str;
	mDexterity = mTempDexterity = dex;
	mConstitution = mTempConstitution = con;
	mIntelligence = mTempIntelligence = int_;
	mCharisma = mTempCharisma = cha;
}

/**
* Print the current player stats.
*/
std::string PlayerStats::Print() {
	std::ostringstream outString;
	outString << "\n" << cBlue << "---\n" << cGreen << "Current Stats\n" << cBlue << "---\n" << cDefault;
	outString << cYellow << "Health: " << cRed << mTempHealth << cDefault << " / " << cRed << mHealth << cDefault << "\n";
	outString << cYellow << "Mana: " << cBlue << mTempMana << cDefault << " / " << cBlue << mMana << cDefault << "\n";
	outString << "\n" << cYellow << "Attributes: Temporary (Maximum)\n";
	outString << cYellow << "Strength:     " << cGreen << mTempStrength << cDefault << " (" << cGreen << mStrength << cDefault << ")\n";
	outString << cYellow << "Dexterity:    " << cGreen << mTempDexterity << cDefault << " (" << cGreen << mDexterity << cDefault << ")\n";
	outString << cYellow << "Constitution: " << cGreen << mTempConstitution << cDefault << " (" << cGreen << mConstitution << cDefault << ")\n";
	outString << cYellow << "Intelligence: " << cGreen << mTempIntelligence << cDefault << " (" << cGreen << mIntelligence << cDefault << ")\n";
	outString << cYellow << "Charisma:     " << cGreen << mTempCharisma << cDefault << " (" << cGreen << mCharisma << cDefault << ")\n";
	outString << cBlue << "---\n" << cDefault;

	return outString.str();
}