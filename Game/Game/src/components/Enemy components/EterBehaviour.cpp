#include "EterBehaviour.h"

EterBehaviour::EterBehaviour(float groundTime)
{
	floorTime = groundTime;
	elapsedTime = 0;
	speeding = 0;
	dest = Vector2D(WIN_WIDTH / 2, 0);
	dir = Vector2D(0, 1);
}
void EterBehaviour::initComponent()
{
	myTransform = gObj->getComponent<Transform>();
}
void EterBehaviour::update()
{
	elapsedTime += SDLApplication::instance()->getDeltaTime();
	if (elapsedTime >= floorTime)
	{
		dir.rotate(myTransform->getVel().angle(dest - myTransform->getPos()) > 0 ? 1.0f : -1.0f);
		speeding += 0.1;
		myTransform->setVel(dir);
	}
	if (myTransform->getPos().getX() == dest.getX() && myTransform->getPos().getY() == dest.getY())
	{
		gObj->setAlive(false);
		// Avisar al contador de eter tambien
	}
}