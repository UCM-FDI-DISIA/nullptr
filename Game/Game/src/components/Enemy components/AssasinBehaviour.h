#pragma once
#include "EnemyBehaviour.h"
#include "../../core/SDLApplication.h"

class AssasinBehaviour: public EnemyBehaviour {
private:
	Vector2D initialDir;
	bool hasBeenCloseToPlayer;
	float attackDistance;
	bool attacked;
	float dashCooldown;
	float elapsedTime;
	float elapsedDash;
	float attackDelay, dashTime;
	float safeDistance;
public:
	AssasinBehaviour(float stopT, float spd, int dmg, float atkDist, float attack, Player* player);
	static const int id = _ENEMY_BEHAVIOUR;
	virtual void update();
	CallBackCol assasinAttack();
	void enemyAttack();
	virtual void initComponent();
	bool close();
	void dash(bool attacking);
};