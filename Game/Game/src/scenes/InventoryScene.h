#pragma once
#include "GameState.h"
#include "../data/PlayerData.h"
#include <vector>

class InventoryScene : public GameState {
private:
	vector<InventoryInfo> info;
	unordered_map<string, vector<InventoryInfo>::iterator> cr;

	vector<GameObject*> deck;
public:
	InventoryScene();

	// Crear un botón especificado en la escena
	void createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key);
	void createSymbol(Vector2D _pos, string key);

	void createDeck();
	void deleteDeck();
	void createLibrary();
};