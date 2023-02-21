#pragma once
#ifndef FUBATTLESCENE_H_
#define FUBATTLESCENE_H_
#include "GameState.h"
#include "../gameObjects/Player.h"
#include "../gameObjects/UI/CardCounter.h"
#include "../node/BattleNode.h"

class BattleScene : public GameState {
private:
	Player* player;
	// Quitar cuando se cree el mapa de combate / Cambiarlo por el tipo de puntero adecuado
	GameObject* floor;
	vector<GameObject*> enemies;
	battleType type;
public:
	// Constructora
	BattleScene(battleType t_);
	static void mainMenu();
	vector<GameObject*>& getEnemies();
};

#endif