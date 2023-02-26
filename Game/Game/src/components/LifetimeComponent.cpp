#pragma once
#include "../core/GameObject.h"
#include "LifetimeComponent.h"
#include "../core/SDLApplication.h"

LifeTimeComponent::LifeTimeComponent(float lifeSpan): lifeSpan(lifeSpan) {
}

void LifeTimeComponent::update()
{
	currentLifeDuration += SDLApplication::instance()->getDeltaTimeSeconds();
	if(currentLifeDuration > lifeSpan)
	{
		gObj->setAlive(false);
	}
}
