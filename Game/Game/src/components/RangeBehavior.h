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
	Vector2D initialDir;
	float moveTime = 0;
	bool stopped = false;
	SDLApplication* game;
	GameState* myScene;
public:
	static const int id = _RANGE_BEHAVIOR;

	RangeBehavior(float spd, float safDist, float stoptime, float moveTime,
		int damage, int attack, Player* player,SDLApplication* game, GameState* scene);
    virtual void initComponent();
	void setDirectionTo();
	virtual void update();
	void attack();
};

