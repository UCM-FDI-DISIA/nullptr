#pragma once
#ifndef FUBATTLESCENE_H_
#define FUBATTLESCENE_H_
#include "GameState.h"
#include "../gameObjects/Player.h"
#include "../gameObjects/MeleeEnemy.h"
#include "../gameObjects/RangedEnemy.h"
#include "../gameObjects/RangedEnemy.h"
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
	BattleScene(int a);
	static void mainMenu();
	vector<GameObject*>& getEnemies();

	// Comunicar cambios a la UI
	void changeUISelected(bool key, int number);
	void discardUI(deque<Card*>::iterator discarded);
	void recreateUI();
};

#endif