#include "PlayerData.h"
#include "../gameObjects/Card Objects/Cards.h"
PlayerData::PlayerData() {
	
	defaultPlayerStats();

	level = 5;
	// Cartas iniciales
	deck.push_back(new SwordCard());
	deck.push_back(new SwordCard());
	deck.push_back(new SwordCard());
	addCardToLibrary(new SwordCard(), 3);

	deck.push_back(new GunCard());
	deck.push_back(new GunCard());
	deck.push_back(new GunCard());
	addCardToLibrary(new GunCard(), 3);

	deck.push_back(new LaserShadesCard());
	deck.push_back(new LaserShadesCard());
	addCardToLibrary(new LaserShadesCard(), 2);

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

void PlayerData::defaultPlayerStats()
{
	money = 0;
	setMaxMana(100);
	setMaxHP(100);
	setCurrHP(100);
	setAttackMult(1);
	setFireRateMult(1);
	setMoney(50);
	playerSpeed = PLAYER_SPEED;
}

void PlayerData::updatePlayerStats()
{
	//para no duplicar los efectos de las reliquias, se resetean las estad�sticas del jugador
	defaultPlayerStats();

	for (auto relic : myRelics) {
		maxMana += relic->mana;
		maxHP += relic->health;
		attackMult += relic->attackMult;
		fireRateMult += relic->cadencyMult;
		playerSpeed += relic->movementVelocity;
	}
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

void PlayerData::addCardToLibrary(Card* newCard, int num)
{
	// A�ado la carta a la libreria
	for(int i=0; i<num;i++)
	library.push_back(newCard);
}

void PlayerData::addRelic(Relic* relic) {
	myRelics.push_back(relic);
}

std::vector<Card*> PlayerData::getLibrary()
{
	return library;
}
