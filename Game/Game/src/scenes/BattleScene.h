#pragma once
#ifndef FUBATTLESCENE_H_
#define FUBATTLESCENE_H_
#include "GameState.h"
#include "../gameObjects/Player Object/Player.h"
#include "../gameObjects/Enemy Objects/MeleeEnemy.h"
#include "../gameObjects/Enemy Objects/RangedEnemy.h"
#include "../gameObjects/Enemy Objects/TankEnemy.h"
#include "../gameObjects/UI/CardCounter.h"
#include "../gameObjects/Node Objects/Node.h"
#include "../gameObjects/Node Objects/BattleNode.h"
#include "../gameObjects/UI/HandUI.h"
#include "../gameObjects/UI/StatisticsUI.h"
#include "../components/Enemy components/EnemyGenerator.h"

class StatisticsUI;
class HandUI;
class BattleScene : public GameState {
private:
	Player* player;
	// Quitar cuando se cree el mapa de combate / Cambiarlo por el tipo de puntero adecuado
	GameObject* floor, * decs;

	// Generador de enemigos
	vector<GameObject*> enemies;
	GameObject* enemyGenerator;
	battleType type;
	GameObject* deck;
	GameObject* pile;

	// - UI -
	// Frame superior de vida, man� y �ter
	StatisticsUI* statistics;
	// Puntero a la mano del jugador en la UI
	HandUI* hand = nullptr;

public:
	// Constructora
	BattleScene(battleType t_);

	// Getters
	inline vector<GameObject*>* getEnemies() { return &enemies; };
	inline void addEnemy(GameObject* enemy) { enemies.push_back(enemy); }
	Player* getPlayer() { return player; };

	// - UI -
	// Comunicar cambios a la UI
	void changeUISelected(bool key, int number);
	void discardUI(deque<Card*>::iterator discarded);
	void recreateUI();

	// Barras de vida y mana
	void OnManaChanges(float value);
	void OnHealthChanges(float value);

	void OnPlayerDies();
	void OnPlayerDamage(float value);
};

#endif