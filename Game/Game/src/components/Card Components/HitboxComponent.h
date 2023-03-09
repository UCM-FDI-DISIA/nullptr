#pragma once
#include "../Component.h"

class HitboxComponent : public Component
{

public:
	virtual void hitboxFunction(GameObject* trgt) {}
};