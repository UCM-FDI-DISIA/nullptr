#pragma once
#include "../../gameObjects/GameObject.h"
#include "LifetimeComponent.h"

LifeTimeComponent::LifeTimeComponent(Uint32 lifespan)
{
	deathTime = SDL_GetTicks() + lifespan;
}

void LifeTimeComponent::update()
{
	if(SDL_GetTicks() > deathTime)
	{
		gObj->setAlive(false);
	}
}
