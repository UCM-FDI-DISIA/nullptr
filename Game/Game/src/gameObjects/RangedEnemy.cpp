#include "RangedEnemy.h"
#include "../components/RangeBehavior.h"
#include "../scenes/BattleScene.h"


RangedEnemy::RangedEnemy(SDLApplication* game, Vector2D pos, Vector2D vel, int life, Player* player, GameState* scene, Transform* camera)
{
	addComponent<Transform>(pos, vel, 30, 60, 0);
	addComponent<Image>(game->getTexture("Enemy"), camera);
	addComponent<RangeBehavior>(1, 200, 3000, 3000, 5, 4, player, game, scene);
	//addComponent<ColliderComponent>();
	//addComponent<HealthComponent>(life);
}