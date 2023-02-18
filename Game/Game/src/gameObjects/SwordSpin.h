#pragma once
#include "../core/GameObject.h"
#include "../components/ColliderComponent.h"
#include "../components/LifetimeComponent.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../core/SDLApplication.h"



class SwordSpin : public GameObject {
public:

	virtual void initGameObject(Vector2D playerPos, SDLApplication* game) {
		addComponent<Transform>(playerPos - Vector2D(25, 25), Vector2D(0, 0), 100, 100);
		addComponent<LifeTimeComponent>(20);
		addComponent<Image>(game->getTexture("Bullet"));
	}
};