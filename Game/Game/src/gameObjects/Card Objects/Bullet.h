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

	virtual void initGameObject(Vector2D pos, Vector2D dir, int dmg, vector<GameObject*>* target) {
		addComponent<BulletBehavior>(dmg, target);
		addComponent<Transform>(pos, dir, 30, 30);
		addComponent<Image>(SDLApplication::getTexture("Bullet"));
		addComponent<LifeTimeComponent>(10000); // Bajar, ahora son 10000 s
		addComponent<ColliderComponent>(getComponent<BulletBehavior>()->getAttack()); // Recibe la función a realizar que esta almacenada en la bala
	}

	// desde aquí, llamad a la otra. o al revés.
	virtual void initGameObject(Vector2D pos, Vector2D dir, int dmg, GameObject* target) {
		vector<GameObject*>* targets = new vector<GameObject*>();
		targets->push_back(target);
		initGameObject(pos, dir, dmg, targets);
	}
};
