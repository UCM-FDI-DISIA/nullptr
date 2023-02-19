#pragma once
#ifndef FUBATTLESCENE_H_
#define FUBATTLESCENE_H_
#include "GameState.h"
#include "../gameObjects/Player.h"
#include "../gameObjects/UI/CardCounter.h"
#include "../gameObjects/UI/HandUI.h"

class HandUI;
class BattleScene : public GameState {
private:
	Player* player;
	// Quitar cuando se cree el mapa de combate / Cambiarlo por el tipo de puntero adecuado
	GameObject* floor;
	vector<GameObject*> enemies;

	// Puntero a la mano del jugador en la UI
	HandUI* hand = nullptr;

public:
	// Constructora
	BattleScene(SDLApplication* _game, int a);
	static void mainMenu(SDLApplication* game);
	vector<GameObject*>& getEnemies();

	// Comunicar cambio a la UI
	void changeUISelected(bool key, int number);
};

#endif