#include "PlayerData.h"
#include "../gameObjects/Card Objects/Cards.h"
PlayerData::PlayerData() {
	maxHP = 100;
	currHP = maxHP;

	maxMana = 100;
	currMana = maxMana;

	fireRateMult = 1;
	attackMult = 1;

	level = 5;


	deck.push_back(new  AssaultRifleCard());

	deck.push_back(new  AssaultRifleCard());

	deck.push_back(new  AssaultRifleCard());

	deck.push_back(new  AssaultRifleCard());

	deck.push_back(new  AssaultRifleCard());

	deck.push_back(new  AssaultRifleCard());

	deck.push_back(new  AssaultRifleCard());

	deck.push_back(new  AssaultRifleCard());

	deck.push_back(new  AssaultRifleCard());

	deck.push_back(new  AssaultRifleCard());

	deck.push_back(new  AssaultRifleCard());

	deck.push_back(new  AssaultRifleCard());

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

std::vector<std::string> PlayerData::getAvailableItems() {
	return avlbRelics;
}

void PlayerData::setDeck(std::vector<Card*> newDeck)
{
	deck = newDeck;
}

void PlayerData::setAvailableItems(std::vector<std::string> newItems) {
	avlbRelics = newItems;
}

void PlayerData::addCardToLibrary(Card* newCard)
{
	library.push_back(newCard);
}

std::vector<Card*> PlayerData::getLibrary()
{
	return library;
}
