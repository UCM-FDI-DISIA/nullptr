#pragma once
#include "../core/GameObject.h"
#include "../core/SDLApplication.h"
#include "../components/Transform.h"
#include "../components/ColliderComponent.h"
#include "../components/LifetimeComponent.h"
#include "../components/BulletBehavior.h"
#include "../gameObjects/Camera.h"
#include "../components/Image.h"


class Bullet:public GameObject
{
public:

	// cleon says: copy paste es muy mal

	virtual void initGameObject(Vector2D pos, Vector2D dir, int dmg, vector<GameObject*>* target) {
		addComponent<BulletBehavior>(dmg, target);
		addComponent<Transform>(pos, dir, 30, 30);
		addComponent<Image>(SDLApplication::getTexture("Bullet"));
		addComponent<LifeTimeComponent>(10000);
		addComponent<ColliderComponent>();
	}

	// desde aquí, llamad a la otra. o al revés.
	virtual void initGameObject(Vector2D pos, Vector2D dir, int dmg, GameObject* target) {
		addComponent<BulletBehavior>(dmg, target);
		addComponent<Transform>(pos, dir, 30, 30);
		addComponent<Image>(SDLApplication::getTexture("Bullet"));
		addComponent<LifeTimeComponent>(10000);
		addComponent<ColliderComponent>();
	}
};
