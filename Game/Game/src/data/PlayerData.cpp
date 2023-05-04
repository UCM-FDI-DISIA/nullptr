#include "PlayerData.h"
#include "../gameObjects/Card Objects/Cards.h"
#include "../data/json/JSON.h"
#include <fstream>
#include "Album.h"
PlayerData::PlayerData() {
	
	defaultPlayerStats();

	for (auto& var : sdlutils().relics().map_)
	{
		avlbRelics.push_back(var.first);
	}

	lastCard = _card_NULL;
}

void PlayerData::defaultPlayerStats() {
	for (auto& var : sdlutils().relics().map_)
	{
		avlbRelics.push_back(var.first);
	}
	library.clear();
	deck.clear();
	myRelics.clear();
	money = 0;
	setMaxMana(100);
	setMaxHP(100);
	setCurrHP(100);
	setAttackMult(1);
	setFireRateMult(1);
	setMoney(0);
	level = 1;
	playerSpeed = PLAYER_SPEED;
	cardGained = true;
	inventoryNotOpen = true;

	// Cartas iniciales
	addCardToLibrary(_card_SPEAR, 3);
	addCardToDeck(_card_SPEAR, 3);
	addCardToLibrary(_card_SWORD, 3);
	addCardToDeck(_card_SWORD, 3);
	addCardToLibrary(_card_GUN, 2);
	addCardToDeck(_card_GUN, 2);
}

void PlayerData::getDataFromJSON() {
	defaultPlayerStats();

	// Load JSON configuration file. We use a unique pointer since we
	// can exit the method in different ways, this way we guarantee that
	// it is always deleted
	std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile(SAVE_FILENAME));

	// check it was loaded correctly
	// the root must be a JSON object
	if (jValueRoot == nullptr || !jValueRoot->IsObject()) {
		throw "Something went wrong while load/parsing '" + SAVE_FILENAME + "'";
	}

	// we know the root is JSONObject
	JSONObject root = jValueRoot->AsObject();
	JSONValue* jValue = nullptr;

	jValue = root["player"];
	if (jValue != nullptr) {
		JSONObject player = jValue->AsObject();
		maxHP = static_cast<int>(player["health"]->AsNumber());
		currHP = static_cast<int>(player["currHP"]->AsNumber());
		maxMana = static_cast<int>(player["mana"]->AsNumber());
		currMana = static_cast<int>(player["currMana"]->AsNumber());
		playerSpeed = static_cast<float>(player["speed"]->AsNumber());
		attackMult = static_cast<float>(player["attack"]->AsNumber());
		fireRateMult = static_cast<float>(player["fireRate"]->AsNumber());
		money = static_cast<int>(player["money"]->AsNumber());
		level = static_cast<int>(player["level"]->AsNumber());
		lastCard = static_cast<CardId>(player["lastCard"]->AsNumber());


		JSONArray jsonRelics = player["relics"]->AsArray();
		for (auto& jsonR : jsonRelics) {
			myRelics.push_back(&sdlutils().relics().at(jsonR->AsString()));
		}
		
		library.clear();
		JSONArray jsonLibrary = player["library"]->AsArray();
		for (auto& jsonC : jsonLibrary) {
			addCardToLibrary(static_cast<CardId>(jsonC->AsNumber()), 1);
		}

		deck.clear();
		JSONArray jsonDeck = player["deck"]->AsArray();
		for (auto& jsonC : jsonDeck) {
			addCardToDeck(static_cast<CardId>(jsonC->AsNumber()), 1);
		}

		gameMap().clearMap();
		gameMap().createMap(SAVE_FILENAME);
	}
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
	player["money"] = new JSONValue(money);
	player["level"] = new JSONValue(level);
	player["lastCard"] = new JSONValue(lastCard);
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
	jsonData["saved"] = new JSONValue(true);

	
	std::ofstream save(SAVE_FILENAME);
	// comprobar que se ha abierto el archivo
	if (!save.is_open()) {
		save.close();
		throw "Could not create save Player Data file";
	}
	std::unique_ptr<JSONValue> jval(new JSONValue(jsonData));
	try {
		// Guardar los detos de la partida en el archivo
		save << JSON::Stringify(&*jval);
	}
	catch (...) {
		// Cerrar el archivo e informar si hubo algún problema al guardar
		save.close();
		throw "Could not save Player Data correctly";
	}
}


bool PlayerData::hasSaveFile() const {
	try {
		// Load JSON configuration file. We use a unique pointer since we
		// can exit the method in different ways, this way we guarantee that
		// it is always deleted
		std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile(SAVE_FILENAME));

		// check it was loaded correctly
		// the root must be a JSON object
		if (jValueRoot == nullptr || !jValueRoot->IsObject()) {
			throw "Something went wrong while load/parsing '" + SAVE_FILENAME + "'";
		}

		// we know the root is JSONObject
		JSONObject root = jValueRoot->AsObject();
		JSONValue* saved = nullptr;

		saved = root["saved"];

		return saved->AsBool();
	}
	catch (...) {
		return false;
	}
}


void PlayerData::loseSavedData() {
	JSONObject jsonData;
	jsonData["saved"] = new JSONValue(false);

	std::ofstream save(SAVE_FILENAME);
	// comprobar que se ha abierto el archivo
	if (!save.is_open()) {
		save.close();
		throw "Could not create save Player Data file";
	}

	std::unique_ptr<JSONValue> jval(new JSONValue(jsonData));
	try {
		// Guardar los detos de la partida en el archivo
		save << JSON::Stringify(&*jval);
	}
	catch (...) {
		// Cerrar el archivo e informar si hubo algún problema al guardar
		save.close();
		throw "Could not save Player Data correctly";
	}
}

std::vector<std::string> PlayerData::getAvailableItems() {
	return avlbRelics;
}

void PlayerData::setAvailableItems(std::vector<std::string> newItems) {
	avlbRelics = newItems;
}

void PlayerData::addCardToLibrary(CardId newCard, int num) {
	// A�ado la carta a la libreria
	for (int i = 0; i < num; i++) {

		library.push_back(newCard);
	}
	cardGained = true;
	Album::instance()->addCard(cardsData().get(Card::getCardIDfromEnum(newCard)));
}

pair<CardId, int> PlayerData::getNewCard() {
	pair<CardId, int> res;
	bool available = cardAvailable();
	if (lastCard == _card_NULL) {
		lastCard = (CardId) SDLApplication::instance()->getRandInt(0, maxCardId);
		while (count(library.begin(), library.end(), lastCard) && available)
		{
			lastCard = (CardId)SDLApplication::instance()->getRandInt(0, maxCardId);
		}
		res = pair<CardId, int>{lastCard, 1};
		addCardToLibrary(lastCard, 1);
	}
	else {
		res =  pair<CardId, int>{lastCard , 2};
		addCardToLibrary(lastCard, 2);
		lastCard = _card_NULL;
	}
	cardGained = true;
	return res;
}

bool PlayerData::cardAvailable() {
	for (int i = 0; i < maxCardId; i++) {
		if (!count(library.begin(), library.end(), (CardId)i)) return true;
	}
	return false;
}

void PlayerData::addRelic(Relic* relic) {
	maxMana += relic->mana;
	maxHP += relic->health;
	attackMult += relic->attackMult / 100.0f;
	fireRateMult += relic->fireRateMult / 100.0f;
	playerSpeed += relic->speed;
	myRelics.push_back(relic);
}

std::vector<CardId> const& PlayerData::getLibrary() {
	return library;
}
void PlayerData::addCardToDeck(CardId newCard, int num)
{
	for (int i = 0; i < num; i++)
	{
		deck.push_back(newCard);
	}
}

std::vector<CardId> const& PlayerData::getDeck() {
	return deck;
}

void PlayerData::setDeck(std::vector<CardId> newDeck)
{
	deck = newDeck;

	setDataToJSON();
}
