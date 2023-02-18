#include "MeleeEnemy.h"
#include "../core/SDLApplication.h"

MeleeEnemy::MeleeEnemy() {}

void MeleeEnemy::initGameObject(SDLApplication* game, Vector2D pos, int life, Player* player) {
	addComponent<Transform>(pos, Vector2D(0,0), 30, 60, 0);
	addComponent<Image>(game->getTexture("Enemy"));
	addComponent<MeleeBehaviour>(1000, float(0.001), 3, 30, 4, player);
	//addComponent<ColliderComponent>();
	//addComponent<HealthComponent>(life);
}