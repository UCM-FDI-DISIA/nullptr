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

	virtual void initGameObject(Vector2D pos, Vector2D dir, int dmg, BattleScene* where) {
		addComponent<Transform>(pos - Vector2D(WIDTH / 2, HEIGHT / 2), dir * BULLET_SPEED, HEIGHT, WIDTH);
		addComponent<ExplosionBehaviour>(dmg, where, 3);
		addComponent<Image>(SDLApplication::getTexture("Bullet"));
		addComponent<ColliderComponent>();
	}
private:
	const float HEIGHT = 30;
	const float WIDTH = 30;
};

