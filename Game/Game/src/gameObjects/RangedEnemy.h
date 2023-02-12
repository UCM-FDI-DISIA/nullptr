#pragma once
#include "../core/GameObject.h"
#include "../components/RangeBehavior.h"
class RangedEnemy:public GameObject
{
public:
	RangedEnemy(Manager* mngr, Vector2D pos, Vector2D vel)
	{
		setContext(mngr);
		addComponent<Transform>(pos, vel, 30, 60, 0);
		addComponent<RangeBehavior>(1, 20, 3, 3);
	}
};


