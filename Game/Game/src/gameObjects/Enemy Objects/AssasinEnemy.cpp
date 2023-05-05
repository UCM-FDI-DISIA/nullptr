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
	addComponent<AssasinBehaviour>(2050, ENEMY_SPEED, MELEE_ATTACK_DAMAGE, MELEE_ENEMY_WIDTH + 100, 200, player);
	addComponent<OnDeath>(3, 1, player->getComponent<Transform>());
	addComponent<EnemyAnimator>(ASSASIN_ENEMY_TEXTURE_KEY, ASSASIN_ENEMY_SPRITE_WIDTH,
		ASSASIN_ENEMY_SPRITE_HEIGHT, ASSASIN_ENEMY_SPRITE_ROWS, ASSASIN_ENEMY_SPRITE_COLS,
		ASSASIN_ENEMY_IDLE_ANIMATION, ASSASIN_ENEMY_MOVEMENT_ANIMATION, ASSASIN_ENEMY_ATTACK_ANIMATION);
	addComponent<EffectController>();
	addComponent<HealthComponent>(life);
	addComponent<StatusComponent>();
}