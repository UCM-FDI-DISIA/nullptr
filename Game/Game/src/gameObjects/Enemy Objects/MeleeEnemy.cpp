#include "MeleeEnemy.h"
#include "../../core/SDLApplication.h"
#include "../../components/General Components/StatusComponent.h"
#include "../../components/General Components/EffectController.h"
#include "../../components/Enemy components/MeleeBehaviour.h"
#include "../../components/Enemy components/EnemyAnimator.h"
#include "../../scenes/BattleScene.h"

void MeleeEnemy::initGameObject(Vector2D pos, int life, Player* player) {
	addComponent<Transform>(pos, Vector2D(0, 0), MELEE_ENEMY_WIDTH * 1.5, MELEE_ENEMY_HEIGHT * 1.5, 0);
	addComponent<ColliderComponent>(_grp_PLAYER);
	addComponent<MeleeBehaviour>(1000, ENEMY_SPEED, MELEE_ATTACK_DAMAGE, MELEE_ENEMY_WIDTH * 1.5, 1000, player);
	addComponent<OnDeath>(3, 1, player->getComponent<Transform>());
	auto anim = addComponent<EnemyAnimator>(MELEE_ENEMY_TEXTURE_KEY,
		MELEE_ENEMY_SPRITE_WIDTH, MELEE_ENEMY_SPRITE_HEIGHT,
		MELEE_ENEMY_SPRITE_ROWS, MELEE_ENEMY_SPRITE_COLS,
		MELEE_ENEMY_IDLE_ANIMATION, MELEE_ENEMY_MOVEMENT_ANIMATION, MELEE_ENEMY_ATTACK_ANIMATION);
	addComponent<EffectController>(anim);
	addComponent<HealthComponent>(life);
	addComponent<StatusComponent>();
}