#pragma once
#include "Component.h"
#include "Transform.h"
#include "../core/Manager.h"
class EnemyBehavior: public Component
{
protected:
	Transform* pos;
	Transform* playerPos;
	float speed;
	// AttackComponent* attack (cuando este cerca del player, envia un mensaje para atacar)
public:
	EnemyBehavior(float spd) : speed(spd){};
	virtual void initComponent()
	{
		pos = gObj->getComponent<Transform>();
		playerPos = mngr->getPlayer->getComponent<Transform>();
	}
	virtual void moveTo() = 0;
	virtual void attack() = 0;
};

