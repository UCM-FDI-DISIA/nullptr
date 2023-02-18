#pragma once
#include "../core/GameObject.h"
#include "../components/ColliderComponent.h"
#include "../components/LifetimeComponent.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../core/SDLApplication.h"



class SwordSlash : public GameObject {
public:

	virtual void initGameObject(Vector2D playerPos, Vector2D dir, SDLApplication* game) {
		addComponent<Transform>(playerPos + dir * 100, Vector2D(0, 0), 50, 50);
		addComponent<LifeTimeComponent>(20);
		addComponent<Image>(game->getTexture("Bullet"));
	}
};