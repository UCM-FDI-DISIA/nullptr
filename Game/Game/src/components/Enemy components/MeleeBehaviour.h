#pragma once
#include "EnemyBehaviour.h"

class MeleeBehaviour :public EnemyBehaviour{
private:
	Vector2D initialDir;
	bool hasBeenCloseToPlayer;
	float attackDistance;
	bool attacked;

	float attackDelay, attackTime;
public:
	MeleeBehaviour(float stopT, float spd, int dmg, float atkDist, float attack, Player* player);
	static const int id = _ENEMY_BEHAVIOUR;
	virtual void update();
	CallBackCol meleeAttack();
	void enemyAttack();
	virtual void initComponent();
	void close();
};