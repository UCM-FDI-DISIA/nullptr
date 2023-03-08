#pragma once
#include "../GameObject.h"
#include "../../core/SDLApplication.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/ColliderComponent.h"
#include "../../components/General Components/LifetimeComponent.h"
#include "../../components/Card Components/ThrownSpearBehaviour.h"
#include "../General Objects/Camera.h"
#include "../../components/General Components/Image.h"


class ThrownSpear :public GameObject
{
public:

	virtual void initGameObject(Vector2D pos, Vector2D dir, int dmg, grpId group) {
		addComponent<Transform>(pos, dir * THROWN_SPEAR_SPEED, 100, 30, Vector2D(1, 0).angle(dir));
		addComponent<Image>(SDLApplication::getTexture("SpearThrust"));
		addComponent<LifeTimeComponent>(10);
		addComponent<ThrownSpearBehaviour>(dmg);
		addComponent<ColliderComponent>(getComponent<ThrownSpearBehaviour>()->spearAttack(), group);
	}
};