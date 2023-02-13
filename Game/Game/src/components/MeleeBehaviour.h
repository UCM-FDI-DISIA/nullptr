#pragma once
#include "EnemyBehavior.h"

class MeleeBehaviour :public EnemyBehavior {
private:
	Vector2D initialDir;
	bool closeToPlayer;
	float attackDistance;
public:
	MeleeBehaviour(float stopT, float spd, int dmg, float atkDist, float attack);
	static const int id = _MELEE_BEHAVIOUR;
	virtual void moveTo();
	virtual void update();
	virtual void initComponent();
	bool close();
};