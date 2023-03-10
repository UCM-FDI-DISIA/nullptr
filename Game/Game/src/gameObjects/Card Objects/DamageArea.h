#pragma once
#include "../GameObject.h"
#include "../../components/General Components/ColliderComponent.h"
#include "../../components/General Components/LifetimeComponent.h"
#include "../../components/Card Components/ConfuseBehaviour.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/Image.h"
#include "../../core/SDLApplication.h"
#include "../../components/Card Components/ExplosionBehaviour.h"



class DamageArea : public GameObject {
public:
	virtual void initGameObject(Vector2D pos, BattleScene* scene, int dmg, int duration) {
		addComponent<Transform>(pos - Vector2D(WIDTH / 2, HEIGHT / 2), Vector2D(0, 0), WIDTH, HEIGHT);
		addComponent<LifeTimeComponent>(duration);
		addComponent<ExplosionBehaviour>(dmg, scene, 3);
		addComponent<ColliderComponent>();
	}

private:
	const float HEIGHT = 600;
	const float WIDTH = 600;
};
