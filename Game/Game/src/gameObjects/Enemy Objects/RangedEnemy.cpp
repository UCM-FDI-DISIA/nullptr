#include "RangedEnemy.h"
#include "../../components/Enemy components/RangeBehaviour.h"
#include "../../components/Enemy components/EnemyAnimator.h"
#include "../../components/General Components/StatusComponent.h"
#include "../../scenes/BattleScene.h"

void RangedEnemy::initGameObject(Vector2D pos,int life, Player* player) {
	addComponent<Transform>(pos, Vector2D(), Constant::getInt("RANGED_ENEMY_WIDTH"), Constant::getInt("RANGED_ENEMY_HEIGHT"), 0);
	addComponent<RangeBehaviour>(1, 200, 3000, 3000, Constant::getInt("RANGED_ATTACK_DAMAGE"), 3, player);
	addComponent<OnDeath>(3, 1, player->getComponent<Transform>());
	addComponent<HealthComponent>(life);
	addComponent<EnemyAnimator>(Constant::getString("RANGED_ENEMY_TEXTURE_KEY"), Constant::getInt("RANGED_ENEMY_SPRITE_WIDTH"),
		Constant::getInt("RANGED_ENEMY_SPRITE_HEIGHT"), Constant::getInt("RANGED_ENEMY_SPRITE_ROWS"), Constant::getInt("RANGED_ENEMY_SPRITE_COLS"),
		Constant::getAnimation("RANGED_ENEMY_IDLE_ANIMATION"), Constant::getAnimation("RANGED_ENEMY_MOVEMENT_ANIMATION"), Constant::getAnimation("RANGED_ENEMY_ATTACK_ANIMATION"));
	addComponent<ColliderComponent>(_grp_PLAYER);
	addComponent<StatusComponent>();
}