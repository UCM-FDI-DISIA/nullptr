#include "RangedEnemy.h"
#include "../components/RangeBehavior.h"
#include "../scenes/BattleScene.h"

void RangedEnemy::initGameObject(Vector2D pos,int life, Player* player)
{
	addComponent<Transform>(pos, Vector2D(0,0), 30, 60, 0);
	addComponent<Image>(SDLApplication::getTexture("Enemy"));
	addComponent<RangeBehavior>(1, 200, 3000, 3000, 50, 3, player);
	addComponent<HealthComponent>(life);
}