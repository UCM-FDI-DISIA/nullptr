#include "RangedEnemy.h"
#include "../../components/Enemy components/RangeBehaviour.h"
#include "../../components/Enemy components/EnemyAnimator.h"
#include "../../components/General Components/StatusComponent.h"
#include "../../components/General Components/EffectController.h"
#include "../../scenes/BattleScene.h"

void RangedEnemy::initGameObject(Vector2D pos,int life, Player* player) {
	addComponent<Transform>(pos, Vector2D(0,0), RANGED_ENEMY_WIDTH, RANGED_ENEMY_HEIGHT, 0);
	addComponent<RangeBehaviour>(1, 200, 3000, 3000, RANGED_ATTACK_DAMAGE, 3, player);
	addComponent<OnDeath>(3, 1, player->getComponent<Transform>());
	addComponent<EnemyAnimator>(RANGED_ENEMY_TEXTURE_KEY, RANGED_ENEMY_SPRITE_WIDTH,
		RANGED_ENEMY_SPRITE_HEIGHT, RANGED_ENEMY_SPRITE_ROWS, RANGED_ENEMY_SPRITE_COLS, 
		RANGED_ENEMY_IDLE_ANIMATION, RANGED_ENEMY_MOVEMENT_ANIMATION, RANGED_ENEMY_ATTACK_ANIMATION);
	addComponent<EffectController>();
	addComponent<HealthComponent>(life);
	addComponent<ColliderComponent>(_grp_PLAYER);
	addComponent<StatusComponent>();
}