#pragma once
#include "../utils/Singleton.h"
#include "../gameObjects/Card Objects/Card.h"
#include <vector>
#include <list>
#include <string>

class Card;
class PlayerData : public Singleton<PlayerData>
{
	friend Singleton<PlayerData>;

	private:
	
	/*
	
	Mazo - lo que se lleva
	Biblioteca - lo que no

	Progreso de la run
	- mapa
	- posicion
	- currentStats
	- items
	
	
	*/

	std::vector<Card*> deck;
	std::vector<Card*> library;
	
	//Lista con todas las reliquias disponibles, saca su key del mapa
	std::vector<std::string> avlbRelics;

	int maxMana;
	int maxHP;
	int currHP;
	int currMana;

	float attackMult, fireRateMult;
	
	int level;

	PlayerData();

	public:

		inline int getMaxMana() { return maxMana; }
		inline int getCurrMana() { return currMana; }
		inline int getMaxHP() { return maxHP; }
		inline int getCurrHP() { return currHP; }
		inline float getAttackMult() { return attackMult; }
		inline float getFireRateMult() { return fireRateMult; }
		inline int getLevel() { return level; }


		inline void setMaxMana(int maxMana) { this->maxMana = maxMana; }
		inline void setCurrMana(int currMana) { this->currMana = currMana; }
		inline void setMaxHP(int maxHP) { this->maxHP = maxHP; }
		inline void setCurrHP(int currHP) { this->currHP = currHP; }
		inline void setAttackMult(float attackMult) { this->attackMult = attackMult; }
		inline void setFireRateMult(float fireRateMult) { this->fireRateMult = fireRateMult; }
		inline void setLevel(int level) { this->level = level; }


		void getDataFromJSON();
		void setDataToJSON();

		std::vector<Card*> getDeck();
		std::vector<std::string> getAvailableItems();

		void setDeck(std::vector<Card*> newDeck);
		void setAvailableItems(std::vector<std::string> newItems);
		int getRelic(std::string key);

		void addCardToLibrary(Card* newCard);
		std::vector<Card*> getLibrary();
		
};

inline PlayerData& pD() {
	return *PlayerData::instance();
}
