#pragma once
#ifndef FUBATTLESCENE_H_
#define FUBATTLESCENE_H_
#include "GameState.h"
#include "../gameObjects/Player.h"
#include "../gameObjects/MeleeEnemy.h"
#include "../gameObjects/RangedEnemy.h"
#include "../gameObjects/RangedEnemy.h"
#include "../gameObjects/UI/CardCounter.h"
#include "../core/SDLApplication.h"
#include "../core/GameObject.h"
#include "../components/ecs.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/ButtonComponent.h"
#include "../components/Animator.h"



class BattleScene : public GameState {
private:
	Player* player;
	// Quitar cuando se cree el mapa de combate / Cambiarlo por el tipo de puntero adecuado
	GameObject* floor, *decs,*vida, *barraVida;
	vector<GameObject*> enemies;
public:
	// Constructora
	BattleScene(int a);
	static void mainMenu();
	void animationB(Animator* animator);
	vector<GameObject*>& getEnemies();
};

#endif