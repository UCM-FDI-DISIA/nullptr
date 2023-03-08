#pragma once
#include "../GameObject.h"
#include "../../core/SDLApplication.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/ColliderComponent.h"
#include "../../components/General Components/LifetimeComponent.h"
#include "../../components/Card Components/BulletBehavior.h"
#include "../General Objects/Camera.h"
#include "../../components/General Components/Image.h"


class Bullet:public GameObject
{
public:
	virtual void initGameObject(Vector2D pos, Vector2D dir, int dmg, grpId trgt) {
		addComponent<Transform>(pos, dir * BULLET_SPEED, 30, 30);
		addComponent<Image>(SDLApplication::getTexture("Bullet"));
		addComponent<LifeTimeComponent>(10);
		addComponent<BulletBehavior>(dmg);
		addComponent<ColliderComponent>(getComponent<BulletBehavior>()->bulletAttack(),trgt);
	}

};
