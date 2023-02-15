#include "MeleeEnemy.h"
#include "../core/SDLApplication.h"

MeleeEnemy::MeleeEnemy(SDLApplication* game, Vector2D pos, Vector2D vel, int life, Player* player, Transform* camera)
{
	addComponent<Transform>(pos, vel, 30, 60, 0);
	addComponent<Image>(game->getTexture("Enemy"), camera);
	addComponent<MeleeBehaviour>(1000, float(0.001), 3, 30, 4, player);
	//addComponent<ColliderComponent>();
	//addComponent<HealthComponent>(life);

}