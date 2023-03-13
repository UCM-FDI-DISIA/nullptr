#include "MeleeEnemy.h"
#include "../../core/SDLApplication.h"
#include "../../components/General Components/StatusComponent.h"

void MeleeEnemy::initGameObject(Vector2D pos, int life, Player* player) {
	addComponent<Transform>(pos, Vector2D(0,0), ENEMY_WIDTH, ENEMY_HEIGHT, 0);
	addComponent<Image>(SDLApplication::getTexture("Enemy"));
	addComponent<ColliderComponent>(_grp_PLAYER);
	addComponent<MeleeBehaviour>(1000, ENEMY_SPEED, 50, 30, 1000, player);
	addComponent<HealthComponent>(life);
	addComponent<StatusComponent>();
}