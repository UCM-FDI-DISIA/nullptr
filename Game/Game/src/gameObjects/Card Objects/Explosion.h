#pragma once
#include "../GameObject.h"
#include "../../components/General Components/ColliderComponent.h"
#include "../../components/General Components/LifetimeComponent.h"
#include "../../components/Card Components/SwordSlashBehaviour.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/Image.h"
#include "../../core/SDLApplication.h"



class Explosion : public GameObject {
public:
	virtual void initGameObject(Vector2D pos, BattleScene* scene, int dmg, grpId trgt) {
		addComponent<Transform>(pos - Vector2D(WIDTH / 2, HEIGHT / 2), Vector2D(0, 0), WIDTH, HEIGHT);
		addComponent<LifeTimeComponent>(0.5);
		addComponent<Image>(SDLApplication::getTexture("Laser"));
		addComponent<SwordSlashBehaviour>(dmg, trgt);
		addComponent<ColliderComponent>(getComponent<SwordSlashBehaviour>()->swordAttack(), trgt);
		
	}

private:
	const float HEIGHT = 250;
	const float WIDTH = 250;
};
