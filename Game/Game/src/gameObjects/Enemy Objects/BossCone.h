#pragma once
#include "../GameObject.h"

class BossCone : public GameObject {
private:
	int damage = 15;
public:
	virtual void initGameObject(Vector2D pos, float rot);
};