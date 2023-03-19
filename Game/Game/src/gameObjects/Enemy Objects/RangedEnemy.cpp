#include "RangedEnemy.h"
#include "../../components/Enemy components/RangeBehaviour.h"
#include "../../components/Enemy components/RangedEnemyAnimator.h"
#include "../../components/General Components/StatusComponent.h"
#include "../../scenes/BattleScene.h"

void RangedEnemy::initGameObject(Vector2D pos,int life, Player* player) {
	addComponent<Transform>(pos, Vector2D(0,0), RANGED_ENEMY_WIDTH, RANGED_ENEMY_HEIGHT, 0);
	addComponent<RangeBehaviour>(1, 200, 3000, 3000, 50, 3, player);
	addComponent<OnDeath>(3, 1, player->getComponent<Transform>());
	addComponent<HealthComponent>(life);
	addComponent<RangedEnemyAnimator>();
	addComponent<ColliderComponent>(_grp_PLAYER);
	addComponent<StatusComponent>();
}