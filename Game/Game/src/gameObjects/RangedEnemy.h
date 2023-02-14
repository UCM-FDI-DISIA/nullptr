#pragma once
#include "../core/GameObject.h"
#include "../components/RangeBehavior.h"
#include "../components/Image.h"
class RangedEnemy:public GameObject
{
public:
	RangedEnemy(SDLApplication* game,Vector2D pos, Vector2D vel, int life, Player* player, BattleScene* scene)
	{
		addComponent<Transform>(pos, vel, 30, 60, 0);
		addComponent<Image>(game->getTexture("Enemy"));
		addComponent<RangeBehavior>(1, 200, 3000, 3000, 5, 4, player, game,scene);
		//addComponent<ColliderComponent>();
		//addComponent<HealthComponent>(life);
	}
};


