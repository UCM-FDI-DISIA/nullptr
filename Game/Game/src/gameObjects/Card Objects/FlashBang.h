#pragma once
#include "../GameObject.h"
#include "../../components/General Components/ColliderComponent.h"
#include "../../components/General Components/LifetimeComponent.h"
#include "../../components/Card Components/ConfuseBehaviour.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/Image.h"
#include "../../core/SDLApplication.h"



class FlashBang : public GameObject {
public:
	virtual void initGameObject(Vector2D pos, BattleScene* scene, float duration, grpId group) {
		addComponent<Transform>(pos - Vector2D(WIDTH / 2, HEIGHT / 2), Vector2D(0, 0), WIDTH, HEIGHT);
		addComponent<LifeTimeComponent>(0.5);
		addComponent<Image>(SDLApplication::getTexture("FlashBang"));
		addComponent<ConfuseBehaviour>(duration, group);
		addComponent<ColliderComponent>(getComponent<ConfuseBehaviour>()->confuseAttack(), group);
	}

private:
	const float HEIGHT = 800;
	const float WIDTH = 800;
};
