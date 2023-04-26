#include "TargetedComponent.h"
#include "../../gameObjects/GameObject.h"
#include "../General Components/Transform.h"
TargetedComponent::TargetedComponent(Transform* player)
{
	playerTransform = player;
	initTime = 1;
	delayTime = BOSS_TARGETED_DELAY;
	elapsedTime = 0;
	maxWidth = 3 * BOSS_ENEMY_WIDTH;
	initCompleted = delayCompleted = false;
	actualRot = 0;
}
void TargetedComponent::initComponent()
{
	myTransform = gObj->getComponent<Transform>();
	originalX = myTransform->getX();
	originalY = myTransform->getY();
}
void TargetedComponent::update()
{
	if (elapsedTime < initTime && !initCompleted && !delayCompleted)
	{
		myTransform->setWidth(maxWidth * 3 / 10 * elapsedTime);
		elapsedTime += SDLApplication::instance()->getDeltaTimeSeconds();
		if (elapsedTime >= initTime) {
			initCompleted = true;
			elapsedTime = 0;
		}
	}
	if (elapsedTime < delayTime && initCompleted && !delayCompleted) {
		elapsedTime += SDLApplication::instance()->getDeltaTimeSeconds(); 
		// Probar con un booleano de si la rotacion a cambiado
		myTransform->rotate(myTransform->getAngle(playerTransform->getPos(), myTransform->getPos())-actualRot);
		actualRot = myTransform->getRotation();
	}
	else if (elapsedTime >= delayTime && initCompleted && !delayCompleted)
	{
		delayCompleted = true;
		initCompleted = false;
		elapsedTime = 0;
	}
	else if (elapsedTime < initTime && delayCompleted && !initCompleted)
	{
		myTransform->setWidth(maxWidth * 3 / 10 + (maxWidth * 7) / 10 * elapsedTime);
		elapsedTime += SDLApplication::instance()->getDeltaTimeSeconds();
		if (elapsedTime >= initTime) {
			initCompleted = true;
			elapsedTime = 0;
		}
	}
	if(delayCompleted && initCompleted) gObj->setAlive(false);


}