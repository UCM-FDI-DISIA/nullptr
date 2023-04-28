#pragma once

#include "NodeScene.h"
#include "../gameObjects/Player Object/Player.h"
#include "../gameObjects/Enemy Objects/MeleeEnemy.h"
#include "../gameObjects/Enemy Objects/RangedEnemy.h"
#include "../gameObjects/Enemy Objects/TankEnemy.h"
#include "../gameObjects/UI/CardCounter.h"
#include "../gameObjects/Node Objects/Node.h"
#include "../components/Enemy components/EnemyGenerator.h"

class StatisticsUI;
class ChargedPortalComponent;
class HandUI;

class BattleScene : public NodeScene {
protected:
	Player* player;
	GameObject *floor, *background, *background1, *background2, *background3;

	// Generador de enemigos
	GameObject* enemyGenerator;
	BattleType type;
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
	BattleScene(BattleType t_, bool tutorial = false);
	// Destructora
	virtual ~BattleScene() { battleSceneOST->haltMusic(); };

	// Getters
	Player* getPlayer() { return player; };

	// Efectos sobre el jugador
	void OnPlayerDies();
	void OnPlayerDamage(float value);

	void changeToGameOverScene();

	// Anade el fondo y suelo
	void addBackgroundAndFloor();
	// Anade la musica
	void addMusic();

	// - UI -
	void createUI();
	void createHand(CardComponent* cc);
	void createCounters(CardComponent* cc);
	void createStatistics(HealthComponent* hc, CardComponent* cc);
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
