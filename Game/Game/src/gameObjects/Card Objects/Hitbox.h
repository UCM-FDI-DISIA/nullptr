#pragma once
#include "../GameObject.h"
#include "../../components/General Components/ColliderComponent.h"
#include "../../components/General Components/LifetimeComponent.h"
#include "../../components/Card Components/HitboxDamageComponent.h"
#include "../../components/Card Components/HitboxStatusComponent.h"
#include "../../components/Card Components/HitboxExplosionComponent.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/Image.h"
#include "../../core/SDLApplication.h"


class Hitbox : public GameObject {
public:

	struct HitboxData
	{
		Vector2D pos, vel, anch;
		float rot, width, height;
		string texture;
		grpId trgt;
	};

	virtual void initGameObject(HitboxData data) {
		addComponent<Transform>(data.pos - Vector2D(data.width/2, data.height/2), data.vel, data.anch, data.width, data.height, data.rot);
		addComponent<Image>(SDLApplication::getTexture(data.texture));
		addComponent<ColliderComponent>(data.trgt);
	}

	virtual void initGameObject(int dmg, bool isDestroyed, bool knockBack, float lifetime, HitboxData data)
	{
		initGameObject(data);
		addComponent<LifeTimeComponent>(lifetime);
		addComponent<HitboxDamageComponent>(dmg, isDestroyed, knockBack);
	}

	virtual void initGameObject(float drtn, HitboxStatusComponent::Status stts, float lifetime, HitboxData data)
	{
		initGameObject(data);
		addComponent<LifeTimeComponent>(lifetime);
		addComponent<HitboxStatusComponent>(stts, drtn);
	}

	virtual void initGameObject(int dmg, bool contact, float lifetime, BattleScene* scene, HitboxData data)
	{
		initGameObject(data);
		addComponent<HitboxExplosionComponent>(dmg, lifetime, contact, scene, data.trgt);
	}

	virtual void initGameObject(int dmg, bool isDestroyed, bool knockBack, float drtn, HitboxStatusComponent::Status stts, float lifetime, HitboxData data)
	{
		initGameObject(dmg, isDestroyed, knockBack, lifetime, data);
		addComponent<HitboxStatusComponent>(stts, drtn);
	}
};
