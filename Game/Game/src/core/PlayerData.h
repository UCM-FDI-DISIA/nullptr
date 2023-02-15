#pragma once
#include "../utils/Singleton.h"
#include "../core/Card.h"
#include <vector>


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

	vector<Card*> deck;
	vector<Card*> library;

	int maxMana;
	int maxHP;
	int currHP;
	int currMana;

	float attackMult, fireRateMult;
	

	PlayerData();

	public:

		int getMaxMana() { return maxMana; }
		int getCurrMana() { return maxMana; }
		int getMaxHP() { return maxMana; }
		int getCurrHP() { return maxMana; }
		float getAttackMult() { return maxMana; }
		float getFireRateMult() { return maxMana; }

		void setMaxMana(int maxMana) { this->maxMana = maxMana; }
		void setCurrMana(int currMana) { this->currMana = currMana; }
		void setMaxHP(int maxHP) { this->maxHP = maxHP; }
		void setCurrHP(int currHP) { this->currHP = currHP; }
		void setAttackMult(float attackMult) { this->attackMult = attackMult; }
		void setFireRateMult(float fireRateMult) { this->maxMana = fireRateMult; }


		void getDataFromJSON();
		void setDataToJSON();

		vector<Card*> getDeck();
		void setDeck(vector<Card*> newDeck);
		void addCardToLibrary(Card* newCard);
		vector<Card*> getLibrary();





};

inline PlayerData& pD() {
	return *PlayerData::instance();
}
