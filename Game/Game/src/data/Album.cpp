#include "Album.h"

// Constructora
Album::Album() : filename("../Game/src/data/game.album.json") {
	auto const& cbt = cardsData().getCardsByTime();
	for (int i = 0; i < 3; ++i) {
		foundCardsByTime[i] = std::vector<bool>(cbt[i].size(), false);
	}
	loadFromJSON();
}

// Carga las cartas del álbum desde archivo json
void Album::loadFromJSON() {
	// si el archivo existe, lo carga
	if ([&]() {
		std::ifstream e(filename);
		bool a = e.is_open();
		e.close();
		return a; }()) {

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
			std::string cardName = val->AsString();
			addCard(cardsData().get(cardName));
		}
	}
}

// Guarda las cartas del álbum en archivo json
void Album::saveToJSON() {
	if (foundCards.size() > 0) {
		std::ofstream save(filename);
		// comprobar que se ha abierto el archivo
		if (!save.is_open()) {
			save.close();
			throw "Could not create save Album file";
		}
		try {
			// Guardar los nombres de las cartas en un JSON array
			save << "[";
			for (CardData& cData : foundCards) {
				save << "\"" << cData.key << "\"";
				if (cData.key != foundCards.rbegin()->key) {
					save << ", ";
				}
			}
			save << "]";
		}
		catch (...) {
			// Cerrar el archivo e informar si hubo algún problema al guardar
			save.close();
			throw "Could not save Album correctly";
		}
	}
}

// Destructora, guarda el album
Album::~Album() {
	saveToJSON();
}

// Añade una carta al álbum si no está ya en él
void Album::addCard(CardData cData) {
	if (!foundCardsNames.count(cData.key)) {
		foundCards.push_back(cData);
		foundCardsNames.insert(cData.key);

		foundCardsByTime[cData.time][cardsData().getCardsIndexByTime()[cData.time].at(cData.key)] = true;
	}
}