#include "PlayerData.h"

void PlayerData::getDataFromJSON()
{
	throw "Sin implementar lololo";
}


void PlayerData::setDataToJSON()
{
}

vector<Card*> PlayerData::getDeck()
{
	return deck;
}

void PlayerData::setDeck(vector<Card*> newDeck)
{
	deck = newDeck;
}

void PlayerData::addCardToLibrary(Card* newCard)
{
	library.push_back(newCard);
}

vector<Card*> PlayerData::getLibrary()
{
	return library;
}
