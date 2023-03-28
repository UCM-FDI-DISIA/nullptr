#pragma once
#include "GameState.h"
#include <map>
#include <vector>


class Card;
struct InventoryInfo {

	int cuantity = 0;
	int cuantityDeck = 0;
	Card* card;

	InventoryInfo() : cuantity(0), cuantityDeck(0), card(nullptr) { };
};

class InventoryScene : public GameState {
private:
	std::map<string,InventoryInfo> inventory;
	vector<int> stats;
public:
	InventoryScene();

	// Crear un botón especificado en la escena
	void createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key);
	void createSymbol(Vector2D _pos, string key, string text, int val);
	void createPanels();
	void createMoneyInfo();
	void createObjects();
};