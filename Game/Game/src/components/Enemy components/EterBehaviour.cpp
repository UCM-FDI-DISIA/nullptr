#include "EterBehaviour.h"

EterBehaviour::EterBehaviour(float groundTime, Transform* player)
{
	floorTime = groundTime;
	elapsedTime = 0;
	speeding = 0;
	plyr = player;
	dest = Vector2D(WIN_WIDTH / 2, 0);
	dir = Vector2D(0, 1);
}
void EterBehaviour::initComponent()
{
	myTransform = gObj->getComponent<Transform>();
}
void EterBehaviour::update()
{
	dest = Vector2D(plyr->getPos().getX(), plyr->getPos().getY() - WIN_HEIGHT / 2);
	elapsedTime += SDLApplication::instance()->getDeltaTime();
	if (elapsedTime >= floorTime)
	{
		dir = dir.rotate(myTransform->getVel().angle(dest - myTransform->getPos()) > 0 ? 0.3f : -0.3f);
		speeding += 0.5;
		myTransform->setVel(dir*speeding);
	}
	if ((myTransform->getPos().getX() <= dest.getX()+ 30 && myTransform->getPos().getX() >= dest.getX() - 30) && myTransform->getPos().getY() <= dest.getY())
	{
		gObj->setAlive(false);
		dynamic_cast<BattleScene*>(gStt)->onEtherChanges(ETHER_VALUE);
	}
}