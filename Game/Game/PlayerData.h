#pragma once
#include ""
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
	

	PlayerData();

	public:

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
