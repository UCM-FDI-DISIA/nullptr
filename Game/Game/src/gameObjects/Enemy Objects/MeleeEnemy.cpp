#include "MeleeEnemy.h"
#include "../../components/Enemy components/MeleeBehaviour.h"
#include "../../components/Enemy components/MeleeEnemyAnimator.h"
#include "../../scenes/BattleScene.h"

void MeleeEnemy::initGameObject(Vector2D pos, int life, Player* player) {
/*
	addComponent<ColliderComponent>(getComponent<MeleeBehaviour>()->meleeAttack(),_grp_PLAYER);
	*/
	addComponent<Transform>(pos, Vector2D(0, 0), MELEE_ENEMY_WIDTH * 1.5, MELEE_ENEMY_HEIGHT * 1.5, 0);
	addComponent<ColliderComponent>(_grp_PLAYER);
	addComponent<MeleeBehaviour>(1000, ENEMY_SPEED, 20, MELEE_ENEMY_WIDTH * 1.5, 1000, player);
	addComponent<OnDeath>(3, 1);
	addComponent<HealthComponent>(life);
	addComponent<MeleeEnemyAnimator>();
}