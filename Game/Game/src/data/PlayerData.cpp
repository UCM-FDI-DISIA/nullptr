#include "PlayerData.h"
#include "../gameObjects/Card Objects/Cards.h"
#include "../data/json/JSON.h"
#include <fstream>
#include "Album.h"
PlayerData::PlayerData() {
	
	defaultPlayerStats();

	level = 5;
	// Cartas iniciales
	addCardToLibrary(_card_TORCH, 3);
	addCardToDeck(_card_TORCH, 3);
	addCardToLibrary(_card_GUN, 3);
	addCardToDeck(_card_GUN, 3);
	addCardToLibrary(_card_PULGA, 2);
	addCardToDeck(_card_PULGA, 2);

	for (auto& var : sdlutils().relics().map_)
	{
		avlbRelics.push_back(var.first);
	}
	PlayerData::setDataToJSON();
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
	playerSpeed = PLAYER_SPEED;
}

void PlayerData::getDataFromJSON() {
	throw "Sin implementar lololo";
}


void PlayerData::setDataToJSON()
{
	JSONObject player;
	player["health"] = new JSONValue(maxHP);
	player["currHP"] = new JSONValue(currHP);
	player["mana"] = new JSONValue(maxMana);
	player["currMana"] = new JSONValue(currMana);
	player["speed"] = new JSONValue(playerSpeed);
	player["attack"] = new JSONValue(attackMult);
	player["fireRate"] = new JSONValue(fireRateMult);
	player["speed"] = new JSONValue(playerSpeed);
	player["money"] = new JSONValue(money);
	player["level"] = new JSONValue(level);
	JSONArray jsonRelics;
	for (Relic* r : myRelics) {
		jsonRelics.push_back(new JSONValue(r->id));
	}
	player["relics"] = new JSONValue(jsonRelics);

	JSONArray jsonDeck;
	for (CardId cId : deck) {
		jsonDeck.push_back(new JSONValue(cId));
	}
	player["deck"] = new JSONValue(jsonDeck);

	JSONArray jsonLibrary;
	for (CardId cId : library) {
		jsonLibrary.push_back(new JSONValue(cId));
	}
	player["library"] = new JSONValue(jsonLibrary);


	JSONObject jsonData;
	jsonData["player"] = new JSONValue(player);
	jsonData["map"] = gameMap().mapToJSON();

	JSONValue* jval = new JSONValue(jsonData);
	
	std::ofstream save("../Game/src/data/game.playerData.json");
	// comprobar que se ha abierto el archivo
	if (!save.is_open()) {
		save.close();
		throw "Could not create save Player Data file";
	}
	try {
		// Guardar los detos de la partida en el archivo
		save << JSON::Stringify(jval);
	}
	catch (...) {
		delete jval;
		// Cerrar el archivo e informar si hubo algún problema al guardar
		save.close();
		throw "Could not save Player Data correctly";
	}
	delete jval;
}

std::vector<std::string> PlayerData::getAvailableItems() {
	return avlbRelics;
}

void PlayerData::setAvailableItems(std::vector<std::string> newItems) {
	avlbRelics = newItems;
}

void PlayerData::addRelic(Relic* relic) {

	maxMana += relic->mana;
	maxHP += relic->health;
	attackMult += relic->attackMult / 100.0f;
	fireRateMult += relic->fireRateMult / 100.0f;
	playerSpeed += relic->speed;
	myRelics.push_back(relic);
}

void PlayerData::addCardToLibrary(CardId newCard, int num) {
	// A�ado la carta a la libreria
	for (int i = 0; i < num; i++) {

		library.push_back(newCard);
	}
	Album::instance()->addCard(cardsData().get(Card::getCardIDfromEnum(newCard)));
}

std::vector<CardId> PlayerData::getLibrary() {
	return library;
}
void PlayerData::addCardToDeck(CardId newCard, int num)
{
	for (int i = 0; i < num; i++)
	{
		deck.push_back(newCard);
	}
}

std::vector<CardId> PlayerData::getDeck() {
	return deck;
}

void PlayerData::setDeck(std::vector<CardId> newDeck)
{
	deck = newDeck;

	setDataToJSON();
}
