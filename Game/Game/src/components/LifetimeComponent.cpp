#pragma once
#include "../core/GameObject.h"
#include "LifetimeComponent.h"
#include "../core/SDLApplication.h"

LifeTimeComponent::LifeTimeComponent(Uint32 lifespan)
{
	time = SDL_GetTicks();
	deathTime = time + lifespan;
}

void LifeTimeComponent::update()
{
	time += SDLApplication::instance()->getDeltaTime();
	if(time > deathTime)
	{
		gObj->setAlive(false);
	}
}
