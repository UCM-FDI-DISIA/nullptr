#pragma once
#include "EnemyBehavior.h"
#include "../gameObjects/Bullet.h"
#include "../scenes/BattleScene.h"
#include "../core/SDLApplication.h"

// Esta clase define el comportamiento del enemigo a distancia
// Se mueve por un tiempo determinado y se queda parado otro
class SDLApplication;
class RangeBehavior :public EnemyBehavior
{
private:
	float safeDistance = 0;
	Vector2D initialDirection;
	float moveTime = 0;
	bool stopped = false;
public:
	static const int id = _RANGE_BEHAVIOR;

	RangeBehavior(float spd, float safDist, float stptime, float mvTime,
		int dmg, int atck, Player* plyr);
    virtual void initComponent();
	void setDirectionTo();
	virtual void update();
	void enemyAttack();
};

