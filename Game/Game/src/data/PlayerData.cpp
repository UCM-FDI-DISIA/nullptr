#include "PlayerData.h"
#include "../gameObjects/Card Objects/Cards.h"
PlayerData::PlayerData() {
	
	defaultPlayerStats();

	level = 5;
	// Cartas iniciales
	deck.push_back(new SwordCard());
	deck.push_back(new SwordCard());
	deck.push_back(new SwordCard());
	// A�adimos al vector de informacion las cartas que tiene el jugador de este tipo y las que est�n de ellas en el mazo
	inventory.push_back(InventoryInfo(3, 3, &cardsData().get("Espada")));
	// La marcamos como a�adida
	receivedCard["Espada"] = prev(inventory.end());

	deck.push_back(new GunCard());
	deck.push_back(new GunCard());
	deck.push_back(new GunCard());
	inventory.push_back(InventoryInfo(3, 3, &cardsData().get("Pistola")));
	receivedCard["Pistola"] = prev(inventory.end());

	deck.push_back(new LaserShadesCard());
	deck.push_back(new LaserShadesCard());
	inventory.push_back(InventoryInfo(2, 2, &cardsData().get("Gafas Laser")));
	receivedCard["Gafas Laser"] = prev(inventory.end());

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
	setMaxHP(1000000);
	setCurrHP(1000);
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
	library.push_back(newCard);

	//Busco si ya la habia recibido antes
	auto it = receivedCard.find(newCard->getName());

	// Si ya la habia recibido simplemente aumento el contador de cartas
	if (it != receivedCard.end()) {
		it->second->cuantity += num;
	}
	// Si no la habia recibido, la creo en el inventario y me guardo su posicion en el mapa 
	else {
		inventory.push_back(InventoryInfo(num, 0, &cardsData().get(newCard->getName())));
		receivedCard[newCard->getName()] = prev(inventory.end());
	}
}

void PlayerData::addRelic(Relic* relic) {
	myRelics.push_back(relic);
}

std::vector<Card*> PlayerData::getLibrary()
{
	return library;
}
