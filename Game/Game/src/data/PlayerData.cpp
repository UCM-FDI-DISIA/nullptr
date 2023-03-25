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


	// Cartas iniciales
	deck.push_back(new SwordCard());
	deck.push_back(new SwordCard());
	deck.push_back(new SwordCard());
	// Añadimos al vector de informacion las cartas que tiene el jugador de este tipo y las que están de ellas en el mazo
	inventory.push_back(InventoryInfo(3, 3, &cardsData().get("Espada")));
	// La marcamos como añadida
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
}

PlayerData::~PlayerData() {
	for (auto& card : deck) {
		delete card;
		card = nullptr;
	}
	deck.clear();
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

void PlayerData::addCardToLibrary(Card* newCard, int num)
{
	// Añado la carta a la libreria
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

std::vector<Card*> PlayerData::getLibrary()
{
	return library;
}
