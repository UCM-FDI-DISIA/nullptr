#include "RangedEnemy.h"
RangedEnemy::RangedEnemy(Manager* Mngr,Vector2D pos, Vector2D vel)
{
	setContext(Mngr);
	addComponent<Transform>( pos, vel, 30, 60, 0);
	addComponent<RangeBehavior>(Mngr, this, getComponent<Transform>(),
		1, 20, 3, 3));
}