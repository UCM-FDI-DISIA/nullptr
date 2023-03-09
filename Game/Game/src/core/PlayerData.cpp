#include "PlayerData.h"
#include "../cards/Cards.h"
PlayerData::PlayerData() {
	maxHP = 100;
	currHP = maxHP;

	maxMana = INT_MAX;
	currMana = maxMana;

	fireRateMult = 1;
	attackMult = 1;

	deck.push_back(new GunCard());

	deck.push_back(new SwordCard());

	deck.push_back(new LaserShadesCard());

	deck.push_back(new SwordCard());

	deck.push_back(new GunCard());

	deck.push_back(new GunCard());

	deck.push_back(new SwordCard());

	deck.push_back(new LaserShadesCard());

	deck.push_back(new SMGCard());

	deck.push_back(new SpearCard());

	deck.push_back(new GunCard());

	deck.push_back(new SwordCard());

	deck.push_back(new LaserShadesCard());

	deck.push_back(new SpearCard());

}

void PlayerData::getDataFromJSON()
{
	throw "Sin implementar lololo";
}


void PlayerData::setDataToJSON()
{
}

std::vector<Card*> PlayerData::getDeck()
{
	return deck;
}

void PlayerData::setDeck(std::vector<Card*> newDeck)
{
	deck = newDeck;
}

void PlayerData::addCardToLibrary(Card* newCard)
{
	library.push_back(newCard);
}

std::vector<Card*> PlayerData::getLibrary()
{
	return library;
}
