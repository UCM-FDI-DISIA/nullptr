#pragma once
#include "EnemyBehaviour.h"
#include "../../gameObjects/Card Objects/Hitbox.h"
#include "../../scenes/BattleScene.h"
#include "../../core/SDLApplication.h"

// Esta clase define el comportamiento del enemigo a distancia
// Se mueve por un tiempo determinado y se queda parado otro
class RangeBehaviour :public EnemyBehaviour
{
private:
	float safeDistance = 0;
	Vector2D initialDirection;
	float moveTime = 0;
	bool stopped = false;
	int shotPattern = 0;

	bool attacking;
	float attackDelay, attackTime;
public:
	static const int id = _ENEMY_BEHAVIOUR;

	RangeBehaviour(float spd, float safDist, float stptime, float mvTime,
		int dmg, int atck, Player* plyr);
    virtual void initComponent();
	void setDirectionTo();
	virtual void update();
	void enemyAttack();

	// Devuelve si el enemigo est� en acci�n de ataque
	inline bool isAttacking() { return attacking; }
};

