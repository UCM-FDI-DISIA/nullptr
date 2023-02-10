#pragma once
#include "Component.h"
#include "Transform.h"
class EnemyBehavior: public Component
{
protected:
	Transform* pos;
	Transform* playerPos;
	float speed;
	float elapsedTime;
	float actualTime;
	// AttackComponent* attack (cuando este cerca del player, envia un mensaje para atacar)
public:
	EnemyBehavior(Manager* mgr, GameObject* gmObj,Transform* Pos, Transform* playerpos, float spd)
	{
		setContext(gmObj, mgr);
		playerPos = playerpos;
		speed = spd;
		pos = Pos;
	}
	virtual void moveTo() = 0;
	virtual void attack() = 0;
};

