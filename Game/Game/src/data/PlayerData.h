#pragma once
#include "../utils/Singleton.h"
#include "../gameObjects/Card Objects/Card.h"
#include "../data/CardsDataContainer.h"
#include "../data/RelicData.h"
#include <vector>
#include <map>
#include <list>
#include <string>

struct InventoryInfo {
	
	int cuantity = 0;
	int cuantityDeck = 0;
	CardData* card;

	InventoryInfo() : cuantity(0), cuantityDeck(0), card(nullptr) { }
	InventoryInfo(int c, int cd, CardData* ca) : cuantity(c), cuantityDeck(cd), card(ca) { }
};

class Card;
class PlayerData : public Singleton<PlayerData>
{
	friend Singleton<PlayerData>;

	private:
	
	/*
	
	Mazo - lo que se lleva
	Biblioteca - lo que no
	Inventario - TODO
	Cartas Recibidas - Mapa de cartas recibidas y su posicion en el vector de inventario

	Progreso de la run
	- mapa
	- posicion
	- currentStats
	- items
	
	
	*/

	std::vector<Card*> deck;
	std::vector<Card*> library;
	std::vector<InventoryInfo> inventory;
	std::unordered_map<string, vector<InventoryInfo>::iterator> receivedCard;
	
	
	//Vector con todas las reliquias disponibles, saca su key del mapa
	std::vector<std::string> avlbRelics;

	//Vector con las reliquias que tiene el jugador
	std::vector<Relic*> myRelics;

	int money;
	int maxMana;
	int maxHP;
	int currHP;
	int currMana;
	float playerSpeed;

	float attackMult, fireRateMult;
	
	int level;

	PlayerData();

	public:
		virtual ~PlayerData();
		inline int getMaxMana() { return maxMana; }
		inline int getCurrMana() { return currMana; }
		inline void resetMana() { currMana = maxMana; }
		inline int getMaxHP() { return maxHP; }
		inline int getCurrHP() { return currHP; }
		inline float getAttackMult() { return attackMult; }
		inline float getFireRateMult() { return fireRateMult; }
		inline float getPlayerMoveSpeed() { return playerSpeed; }
		inline float getMoney() { return money; }
		inline int getLevel() { return level; }
		inline vector<Relic*> getRelics() { return myRelics; }
		inline vector<InventoryInfo> getInventoryInfo() { return inventory; }
		inline unordered_map<string, vector<InventoryInfo>::iterator> getReceivedCards() { return receivedCard; }

		inline void setMaxMana(int maxMana) { this->maxMana = maxMana; }
		inline void setCurrMana(int currMana) { this->currMana = currMana; }
		inline void setMaxHP(int maxHP) { this->maxHP = maxHP; }
		inline void setCurrHP(int currHP) { this->currHP = currHP; }
		inline void setAttackMult(float attackMult) { this->attackMult = attackMult; }
		inline void setFireRateMult(float fireRateMult) { this->fireRateMult = fireRateMult; }
		inline void setLevel(int level) { this->level = level; }
		inline void setMoney(int mon) { money += mon; }
		inline void getPlayerMoveSpeed(float newMoveSpeed) { playerSpeed = newMoveSpeed; }
		void defaultPlayerStats();
		void updatePlayerStats();

		void getDataFromJSON();
		void setDataToJSON();

		std::vector<Card*> getDeck();
		std::vector<std::string> getAvailableItems();
		

		void setDeck(std::vector<Card*> newDeck);
		void addCardToLibrary(Card* newCard, int num);
		void setAvailableItems(std::vector<std::string> newItems);

		void addRelic(Relic* relic);
		std::vector<Card*> getLibrary();
		
};

inline PlayerData& pD() {
	return *PlayerData::instance();
}
