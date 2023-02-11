#pragma once
#include "../core/GameObject.h"
#include "../components/RangeBehavior.h"
class RangedEnemy:public GameObject
{
public:
	RangedEnemy(Manager* mngr, Vector2D pos, Vector2D vel);
	virtual ~RangedEnemy();

private:

};


