#include "BossEnemy.h"
#include "../../components/Enemy components/BossBehaviour.h"
#include "../../components/Enemy components/BossAnimator.h"
#include "../../components/General Components/StatusComponent.h"
#include "../../scenes/BattleScene.h"

void BossEnemy::initGameObject(Vector2D pos, int life, Player* player, CallBack cb) {
	addComponent<Transform>(pos, Vector2D(0, 0), BOSS_ENEMY_WIDTH, BOSS_ENEMY_HEIGHT, 0);
	addComponent<OnDeath>(3, 1, player->getComponent<Transform>(), cb);
	addComponent<HealthComponent>(life);
	addComponent<BossBehaviour>(1, 200, 3000, 3000, 50, 3, player);
	addComponent<BossAnimator>(BOSS_ENEMY_TEXTURE_KEY, BOSS_ENEMY_SPRITE_WIDTH,
		BOSS_ENEMY_SPRITE_HEIGHT, BOSS_ENEMY_SPRITE_ROWS, BOSS_ENEMY_SPRITE_COLS,
		BOSS_ENEMY_IDLE_ANIMATION);

	addComponent<ColliderComponent>(_grp_PLAYER);
	addComponent<StatusComponent>();
}