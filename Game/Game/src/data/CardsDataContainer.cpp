#include "CardsDataContainer.h"
#include "../core/SDLApplication.h"

// Constructora
CardsDataContainer::CardsDataContainer() :
	cardsDatas(cardsDataMap, "cards") {
	readFromJSON("../Game/src/data/game.cards.json");
}

CardTime CardsDataContainer::stringToCardTime(std::string t) {
	if (t == "Past") return _CardPast;
	if (t == "Present") return _CardPresent;
	if (t == "Future") return _CardFuture;
	throw "Invalid card time.";
}

// Lee la información de las cartas desde JSON
void CardsDataContainer::readFromJSON(std::string filename) {
	// Load JSON configuration file. We use a unique pointer since we
	// can exit the method in different ways, this way we guarantee that
	// it is always deleted
	std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile(filename));

	// check it was loaded correctly
	// the root must be a JSON array
	if (jValueRoot == nullptr || !jValueRoot->IsArray()) {
		throw "Something went wrong while load/parsing '" + filename + "'";
	}

	// we know the root is JSONArray
	JSONArray cardsRoot = jValueRoot->AsArray();
	// load cards
	for (auto& val : cardsRoot) {
		JSONObject vObj = val->AsObject();
		// Leer la información de la carta
		CardData card;
		card.key = vObj["key"]->AsString();
		card.name = vObj["name"]->AsString();
		card.attackText = vObj["attackText"]->AsString();
		card.abilityText = vObj["abilityText"]->AsString();
		card.damage = static_cast<int>(vObj["damage"]->AsNumber());
		card.maxUses = static_cast<int>(vObj["maxUses"]->AsNumber());
		card.mana = static_cast<int>(vObj["mana"]->AsNumber());
		card.downTime = static_cast<float>(vObj["downTime"]->AsNumber());
		card.texture = SDLApplication::getTexture(vObj["textureKey"]->AsString());
		card.time = stringToCardTime(vObj["time"]->AsString());
		// Añadir la información de la carta al map que las almacena
		cardsDataMap[card.key] = card;
		cardsByTime[card.time].push_back(card);
		cardsIndexByTime[card.time][card.key] = cardsByTime[card.time].size() - 1;
	}
}