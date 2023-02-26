#include "RangedEnemy.h"
#include "../../components/Enemy components/RangeBehaviour.h"
#include "../../scenes/BattleScene.h"

void RangedEnemy::initGameObject(Vector2D pos,int life, Player* player)
{
	addComponent<Transform>(pos, Vector2D(0,0), ENEMY_WIDTH, ENEMY_HEIGHT, 0);
	addComponent<Image>(SDLApplication::getTexture("Enemy"));
	addComponent<RangeBehaviour>(1, 200, 3000, 3000, 50, 3, player);
	addComponent<HealthComponent>(life);
}