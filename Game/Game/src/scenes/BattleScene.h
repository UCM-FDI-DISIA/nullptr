#pragma once
#ifndef FUBATTLESCENE_H_
#define FUBATTLESCENE_H_
#include "NodeScene.h"
#include "../gameObjects/Player Object/Player.h"
#include "../gameObjects/Enemy Objects/MeleeEnemy.h"
#include "../gameObjects/Enemy Objects/RangedEnemy.h"
#include "../gameObjects/Enemy Objects/TankEnemy.h"
#include "../gameObjects/UI/CardCounter.h"
#include "../gameObjects/Node Objects/Node.h"
#include "../gameObjects/Node Objects/BattleNode.h"
#include "../gameObjects/UI/HandUI.h"
#include "../components/Enemy components/EnemyGenerator.h"

class HandUI;
class BattleScene : public NodeScene {
private:
	Player* player;
	// Quitar cuando se cree el mapa de combate / Cambiarlo por el tipo de puntero adecuado
	GameObject* floor, *decs,*vida, *barraVida;
	GameObject* mana;
	GameObject* barraMana;
	GameObject* enemyGenerator;

	vector<GameObject*> enemies;
	battleType type;
	GameObject* deck;
	GameObject* pile;
	// Puntero a la mano del jugador en la UI
	HandUI* hand = nullptr;
public:
	// Constructora
	BattleScene(battleType t_);
	static void mainMenu();
	//Metodos virtuales
	virtual void update();
	// Comunicar cambios a la UI
	void changeUISelected(bool key, int number);
	void discardUI(deque<Card*>::iterator discarded);
	void recreateUI();
	vector<GameObject*>* getEnemies();
	inline void addEnemy(GameObject* enemy) { enemies.push_back(enemy); }
	Player* getPlayer() { return player; };

	void createLifeBar();
	void createManaBar();
	void OnPlayerDies();
	void OnManaChanges();
};

#endif