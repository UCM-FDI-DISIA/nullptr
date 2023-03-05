#include "MeleeEnemy.h"
#include "../core/SDLApplication.h"

void MeleeEnemy::initGameObject(Vector2D pos, int life, Player* player) {
	addComponent<Transform>(pos, Vector2D(0,0), MELEE_ENEMY_INITIAL_WIDTH, MELEE_ENEMY_INITIAL_HEIGHT, 0);
	//addComponent<Image>(SDLApplication::getTexture("Enemy"));
	addComponent<MeleeBehaviour>(1000, float(0.001), 3, 30, 1000, player);
	addComponent<ColliderComponent>();
	addComponent<HealthComponent>(life);
	addComponent<EnemyAnimator>(SDLApplication::getTexture(MELE_ENEMY), MELEE_ENEMY_SPRITE_WIDTH, MELEE_ENEMY_SPRITE_HEIGHT,
		MELEE_ENEMY_SPRITE_ROWS, MELEE_ENEMY_SPRITE_COLS);

}