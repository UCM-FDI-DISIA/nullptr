#include "TentacleBehaviour.h"
#include "../../gameObjects/GameObject.h"
#include "../General Components/Transform.h"
TentacleBehaviour::TentacleBehaviour(bool mirror)
{
	initTime = 1;
	rotationTime = BOSS_CLOCK_ATTACKDURATION;
	delayTime = BOSS_CLOCK_DELAYTIME;
	elapsedTime = 0;
	maxWidth = 2 * BOSS_ENEMY_WIDTH;
	rotationCompleted = initCompleted = delayCompleted = false;
	isMirror = mirror;
}
void TentacleBehaviour::initComponent()
{
	myTransform = gObj->getComponent<Transform>();
	originalX = myTransform->getX();
	originalY = myTransform->getY();
}
void TentacleBehaviour::update()
{
	if (elapsedTime < initTime && !initCompleted && !delayCompleted)
	{
		myTransform->setWidth( maxWidth / 10 * elapsedTime);
		elapsedTime += SDLApplication::instance()->getDeltaTimeSeconds();
		if (elapsedTime >= initTime) {
			initCompleted = true;
			elapsedTime = 0;
		}
	}
	else if (elapsedTime >= delayTime && initCompleted && !delayCompleted)
	{
		delayCompleted = true;
		initCompleted = false;
		elapsedTime = 0;
	}
	else if (elapsedTime < initTime && delayCompleted && !initCompleted)
	{
		myTransform->setWidth( maxWidth / 10 + (maxWidth*9)/10 * elapsedTime);
		elapsedTime += SDLApplication::instance()->getDeltaTimeSeconds();
		if (elapsedTime >= initTime) {
			initCompleted = true;
			elapsedTime = 0;
		}
	}
	else if (elapsedTime < rotationTime && !rotationCompleted && delayCompleted && initCompleted)
	{
		elapsedTime += SDLApplication::instance()->getDeltaTimeSeconds();
		float angle = 180 * (SDLApplication::instance()->getDeltaTimeSeconds() / rotationTime);
		myTransform->rotate(angle);
		if (elapsedTime >= rotationTime) {
			rotationCompleted = true;
			elapsedTime = 0;
			gObj->setAlive(false);
		}
	}
	if (elapsedTime < delayTime && initCompleted && !delayCompleted) elapsedTime += SDLApplication::instance()->getDeltaTimeSeconds();


}