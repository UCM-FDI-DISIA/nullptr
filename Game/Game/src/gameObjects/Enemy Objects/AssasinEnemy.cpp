#include "AssasinEnemy.h"
#include "../../core/SDLApplication.h"
#include "../../components/General Components/StatusComponent.h"
#include "../../components/General Components/EffectController.h"
#include "../../components/Enemy components/AssasinBehaviour.h"
#include "../../components/Enemy components/EnemyAnimator.h"
#include "../../scenes/BattleScene.h"

void AssasinEnemy::initGameObject(Vector2D pos, int life, Player* player) {
	addComponent<Transform>(pos, Vector2D(0, 0), MELEE_ENEMY_WIDTH, MELEE_ENEMY_HEIGHT);
	addComponent<ColliderComponent>(_grp_PLAYER);
	addComponent<AssasinBehaviour>(125, ENEMY_SPEED, MELEE_ATTACK_DAMAGE, MELEE_ENEMY_WIDTH + 100, 2000, player);
	addComponent<OnDeath>(3, 1, player->getComponent<Transform>());
	addComponent<EnemyAnimator>(RANGED_ENEMY_TEXTURE_KEY, RANGED_ENEMY_SPRITE_WIDTH,
		RANGED_ENEMY_SPRITE_HEIGHT, RANGED_ENEMY_SPRITE_ROWS, RANGED_ENEMY_SPRITE_COLS,
		RANGED_ENEMY_IDLE_ANIMATION, RANGED_ENEMY_MOVEMENT_ANIMATION, RANGED_ENEMY_ATTACK_ANIMATION);
	addComponent<EffectController>();
	addComponent<HealthComponent>(life);
	addComponent<StatusComponent>();
}