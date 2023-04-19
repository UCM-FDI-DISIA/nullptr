#pragma once
#include "EnemyBehaviour.h"
#include "../../gameObjects/Card Objects/Hitbox.h"
#include "../../scenes/BattleScene.h"
#include "../../core/SDLApplication.h"
#include <cmath>

// Esta clase define el comportamiento del enemigo a distancia
// Se mueve por un tiempo determinado y se queda parado otro
class BossBehaviour :public EnemyBehaviour
{
private:
	float safeDistance = 0;
	Vector2D initialDirection;
	float moveTime = 0;
	bool stopped = false;
	int shotPattern = 0;
	float attackDelay, attackTime;
	int attackState = 0;
public:
	static const int id = _ENEMY_BEHAVIOUR;

	BossBehaviour(float spd, float safDist, float stptime, float mvTime,
		int dmg, int atck, Player* plyr);
	virtual void initComponent();
	void setDirectionTo();
	virtual void update();
	void enemyAttack();
	void coneAttack();
	void bulletHellAttack();
	void tentacleDirectedAttack();
	void sprinklerAttack();
	void grenadeAttack();
};

