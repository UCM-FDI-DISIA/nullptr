#include "ExplosionBehaviour.h"
#include "../../GameObjects/Card Objects/Explosion.h"


void ExplosionBehaviour::initComponent()
{
	tr = gObj->getComponent<Transform>();
	target = scene->getEnemies();
}

void ExplosionBehaviour::update()
{
	currentLifeDuration += SDLApplication::instance()->getDeltaTimeSeconds();
	if (currentLifeDuration > lifeSpan)
	{
		scene->addGameObject<Explosion>(tr->getCenter(),scene, damage);
		gObj->setAlive(false);
	}

	for (int i = 0; i < target->size(); i++) {
		if (gObj->getComponent<ColliderComponent>()->
			hasCollided((*target)[i]->getComponent<Transform>())) {
			scene->addGameObject<Explosion>(tr->getCenter(), scene, damage);
			gObj->setAlive(false);
		}
	}
}
