#include "MeleeEnemy.h"
#include "../core/SDLApplication.h"

void MeleeEnemy::initGameObject(Vector2D pos, int life, Player* player) {
	addComponent<Transform>(pos, Vector2D(0,0), MELE_ENEMY_INITIAL_WIDTH, MELE_ENEMY_INITIAL_HEIGHT, 0);
	//addComponent<Image>(SDLApplication::getTexture("Enemy"));
	addComponent<MeleeBehaviour>(1000, float(0.001), 3, 30, 1000, player);
	addComponent<ColliderComponent>();
	addComponent<HealthComponent>(life);
	addComponent<EnemyAnimator>(SDLApplication::getTexture(MELE_ENEMY), MELE_ENEMY_SPRITE_WIDTH, MELE_ENEMY_SPRITE_HEIGHT,
		MELE_ENEMY_SPRITE_ROWS, MELE_ENEMY_SPRITE_COLS);

}