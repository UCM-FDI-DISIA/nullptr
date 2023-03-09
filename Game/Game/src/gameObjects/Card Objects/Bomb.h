#pragma once
#include "../GameObject.h"
#include "../../core/SDLApplication.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/ColliderComponent.h"
#include "../../components/General Components/LifetimeComponent.h"
#include "../../components/Card Components/ExplosionBehaviour.h"
#include "../General Objects/Camera.h"
#include "../../components/General Components/Image.h"


class Bomb :public GameObject
{
public:

	virtual void initGameObject(Vector2D pos, Vector2D dir, int dmg, BattleScene* where, grpId trgt) {
		addComponent<Transform>(pos - Vector2D(WIDTH / 2, HEIGHT / 2), dir * BULLET_SPEED, HEIGHT, WIDTH);
		addComponent<ExplosionBehaviour>(dmg, where, 3, trgt);
		addComponent<Image>(SDLApplication::getTexture("Bullet"));
		addComponent<ColliderComponent>(getComponent<ExplosionBehaviour>()->explosionAttack(), trgt);
	}
private:
	const float HEIGHT = 16;
	const float WIDTH = 16;
};

