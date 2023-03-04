#include "ExplosionBehaviour.h"
#include "../../GameObjects/Card Objects/Explosion.h"


void ExplosionBehaviour::initComponent()
{
	tr = gObj->getComponent<Transform>();
}

void ExplosionBehaviour::update()
{
	currentLifeDuration += SDLApplication::instance()->getDeltaTimeSeconds();
	if (currentLifeDuration > lifeSpan)
	{
		scene->addGameObject<Explosion>(tr->getCenter(),scene, damage);
		gObj->setAlive(false);
	}
}
