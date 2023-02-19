#pragma once
#ifndef FUBATTLESCENE_H_
#define FUBATTLESCENE_H_
#include "GameState.h"
#include "../gameObjects/Player.h"
#include "../gameObjects/UI/CardCounter.h"

class BattleScene : public GameState {
private:
	Player* player;
	// Quitar cuando se cree el mapa de combate / Cambiarlo por el tipo de puntero adecuado
	GameObject* floor;
	vector<GameObject*> enemies;
public:
	// Constructora
	BattleScene(SDLApplication* _game, int a);
	static void mainMenu(SDLApplication* game);
	vector<GameObject*>& getEnemies();
	void OnPlayerDies(SDLApplication* game);
};

#endif