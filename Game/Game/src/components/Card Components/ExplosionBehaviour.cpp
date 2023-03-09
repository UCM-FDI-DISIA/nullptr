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
		scene->addGameObject<Explosion>(_grp_PLYR_ATTACK, tr->getCenter(), scene, damage, target);
		gObj->setAlive(false);
	}
}
CallBackCol ExplosionBehaviour::explosionAttack()
{
	return [&](GameObject* gameObject) {
		scene->addGameObject<Explosion>(_grp_PLYR_ATTACK, tr->getCenter(), scene, damage, target);
		gObj->setAlive(false);
	};
}
