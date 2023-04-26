#include "PlayerData.h"
#include "../gameObjects/Card Objects/Cards.h"
PlayerData::PlayerData() {
	
	defaultPlayerStats();

	level = 5;
	// Cartas iniciales
	deck.push_back(new TorchCard());
	deck.push_back(new TorchCard());
	deck.push_back(new TorchCard());
	addCardToLibrary(_card_TORCH, 3);
	addCardToDeckId(_card_TORCH, 3);

	deck.push_back(new GunCard());
	deck.push_back(new GunCard());
	deck.push_back(new GunCard());
	addCardToLibrary(_card_GUN, 3);
	addCardToDeckId(_card_GUN, 3);
	deck.push_back(new PulgaCard());
	deck.push_back(new PulgaCard());
	addCardToLibrary(_card_PULGA, 2);
	addCardToDeckId(_card_PULGA, 2);

	for (auto& var : sdlutils().relics().map_)
	{
		avlbRelics.push_back(var.first);
	}
}

PlayerData::~PlayerData() {
	for (auto& card : deck) {
		delete card;
		card = nullptr;
	}
	deck.clear(); 
	
}

void PlayerData::defaultPlayerStats() {
	for (auto& var : sdlutils().relics().map_)
	{
		avlbRelics.push_back(var.first);
	}
	myRelics.clear();
	money = 0;
	setMaxMana(100);
	setMaxHP(100);
	setCurrHP(1000);
	setAttackMult(1);
	setFireRateMult(1);
	setMoney(999);
	playerSpeed = Constant::getFloat("PLAYER_SPEED");
}

void PlayerData::getDataFromJSON() {
	throw "Sin implementar lololo";
}


void PlayerData::setDataToJSON()
{
}

std::vector<Card*> PlayerData::getDeck() {
	return deck;
}

std::vector<std::string> PlayerData::getAvailableItems() {
	return avlbRelics;
}

void PlayerData::setDeck(std::vector<Card*> newDeck) {
	for (auto& card : deck) {
		delete card;
		card = nullptr;
	}
	deck.clear();
	deck = newDeck;
}

void PlayerData::setAvailableItems(std::vector<std::string> newItems) {
	avlbRelics = newItems;
}

void PlayerData::addCardToLibrary(CardId newCard, int num) {
	// A�ado la carta a la libreria
	for (int i = 0; i < num; i++) {

		library.push_back(newCard);
	}
}

void PlayerData::addRelic(Relic* relic) {

	maxMana += relic->mana;
	maxHP += relic->health;
	attackMult += relic->attackMult/100.0f;
	fireRateMult += relic->fireRateMult/100.0f;
	playerSpeed += relic->speed;
	myRelics.push_back(relic);
}

std::vector<CardId> PlayerData::getLibrary() {
	return library;
}
void PlayerData::addCardToDeckId(CardId newCard, int num)
{
	for (int i = 0; i < num; i++)
	{
		deckIds.push_back(newCard);
	}
}

std::vector<CardId> PlayerData::getDeckIds()
{
	return deckIds;
}
void PlayerData::setDeckId(std::vector<CardId> newDeck)
{
	deckIds = newDeck;
}
