#pragma once

#include "../utils/Singleton.h"
#include "../components/ecs.h"
#include "CardData.h"
#include "json/JSON.h"
#include "../sdlutils/SDLUtils.h"

class CardsDataContainer : public Singleton<CardsDataContainer> {
	friend Singleton<CardsDataContainer>;
private:
	unordered_map<std::string, CardData> cardsDataMap;
	SDLUtils::map_access_wrapper<CardData> cardsDatas;
	// Constructora
	CardsDataContainer();
	// Lee la información de las cartas desde JSON
	void readFromJSON(std::string filename);
public:
	// Devuelve el struct CardData pedido
	inline auto& get(std::string key) {
		return cardsDatas.at(key);
	}
};

// Devuelve una referencia a la instancia a CardsDataContainer
inline CardsDataContainer& cardsData() {
	return *CardsDataContainer::instance();
}