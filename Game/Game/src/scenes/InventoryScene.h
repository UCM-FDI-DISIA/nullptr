#pragma once
#include "GameState.h"
#include "../gameObjects/UI/InventoryCard.h"
#include <vector>

class InventoryScene : public GameState {
private:
	vector<InventoryInfo> info;
	unordered_map<string, vector<InventoryInfo>::iterator> cr;
	vector<int> deck;
public:
	InventoryScene();

	// Crear un botón especificado en la escena
	void createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key);
	void createSymbol(Vector2D _pos, string key);
	void createPanels();

	void removeFromDeck(int ind);
	int getFirstDeckPos();
};