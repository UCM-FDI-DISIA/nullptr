#pragma once

#include "NodeScene.h"
#include "../gameObjects/Player Object/Player.h"
#include "../gameObjects/Enemy Objects/MeleeEnemy.h"
#include "../gameObjects/Enemy Objects/RangedEnemy.h"
#include "../gameObjects/Enemy Objects/TankEnemy.h"
#include "../gameObjects/UI/CardCounter.h"
#include "../gameObjects/Node Objects/Node.h"
#include "../gameObjects/UI/HandUI.h"
#include "../gameObjects/UI/StatisticsUI.h"
#include "../components/Enemy components/EnemyGenerator.h"

class StatisticsUI;
class HandUI;
class BattleScene : public NodeScene {
private:
	Player* player;
	GameObject *floor, *background, *background1, *background2, *background3;

	// Generador de enemigos
	vector<GameObject*> enemies;
	GameObject* enemyGenerator;
	BattleType type;
	GameObject* deck;
	GameObject* pile;
	Music* battleSceneOST;
	// - UI -
	// Frame superior de vida, man� y �ter
	StatisticsUI* statistics;
	// Puntero a los contadores de cartas
	CardCounter* cardContLeft;
	CardCounter* cardContRight;
	// Puntero a la mano del jugador en la UI
	HandUI* hand;

public:
	// Constructora
	BattleScene(BattleType t_);
	// Destructora
	virtual ~BattleScene() { battleSceneOST->haltMusic(); };

	// Getters
	inline vector<GameObject*>* getEnemies() { return &enemies; };
	inline void addEnemy(GameObject* enemy) { enemies.push_back(enemy); }
	Player* getPlayer() { return player; };

	// Efectos sobre el jugador
	void OnPlayerDies();
	void OnPlayerDamage(float value);

	void changeToGameOverScene();

	// - UI -
	// Comunicar cambios a la UI
	void changeUISelected(bool key, int number);
	void discardUI(deque<Card*>::iterator discarded);
	void recreateUI();
	void changeAmmoUI(deque<Card*>::iterator used);
	// Barras de vida y mana
	void onManaChanges(float value);
	void onHealthChanges(float value);
	void onEtherChanges(float value);
};
