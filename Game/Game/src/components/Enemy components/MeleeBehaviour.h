#pragma once
#include "EnemyBehaviour.h"

class MeleeBehaviour :public EnemyBehaviour {
private:
	Vector2D initialDir;
	bool hasBeenCloseToPlayer;
	float attackDistance;
	bool attacked;

	bool attacking;
	float attackDelay, attackTime;
public:
	MeleeBehaviour(float stopT, float spd, int dmg, float atkDist, float attack, Player* player);
	static const int id = _MELEE_BEHAVIOUR;
	virtual void update();
	virtual void initComponent();
	CallBackCol meleeAttack();
	void close();
	// Devuelve si el enemigo está en acción de ataque
	inline bool isAttacking() { return attacking; }
};