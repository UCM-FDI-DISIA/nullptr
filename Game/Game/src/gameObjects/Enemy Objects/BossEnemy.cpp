#include "BossEnemy.h"
#include "../../components/Enemy components/BossBehaviour.h"
#include "../../components/Enemy components/EnemyAnimator.h"
#include "../../components/General Components/StatusComponent.h"
#include "../../scenes/BattleScene.h"

void BossEnemy::initGameObject(Vector2D pos, int life, Player* player) {
	addComponent<Transform>(pos, Vector2D(0, 0), BOSS_ENEMY_WIDTH, BOSS_ENEMY_HEIGHT, 0);
	addComponent<OnDeath>(3, 1, player->getComponent<Transform>());
	addComponent<HealthComponent>(life);
	addComponent<BossBehaviour>(1, 200, 3000, 3000, 50, 3, player);
	auto animator = addComponent<EnemyAnimator>(BOSS_ENEMY_TEXTURE_KEY, BOSS_ENEMY_SPRITE_WIDTH,
		BOSS_ENEMY_SPRITE_HEIGHT, BOSS_ENEMY_SPRITE_ROWS, BOSS_ENEMY_SPRITE_COLS,
		BOSS_ENEMY_IDLE_ANIMATION, BOSS_ENEMY_MOVEMENT_ANIMATION, BOSS_ENEMY_ATTACK_ANIMATION);

	animator->createAnim("BulletHell", BOSS_ENEMY_BULLETHELL_ANIMATION);
	animator->createAnim("GrenadeAttack", BOSS_ENEMY_GRENADE_ATTACK_ANIMATION);

	addComponent<ColliderComponent>(_grp_PLAYER);
	addComponent<StatusComponent>();
}