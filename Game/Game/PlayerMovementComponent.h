#pragma once
#include "../Game/src/core/GameObject.h"
#include "../Game/src/components/Component.h"
#include "../Game/src/components/Transform.h"

const int playerSpeed = 10;

class PlayerMovementComponent : public Component
{
private:
	Transform* transform;

public:
	static const int id = _PLAYERMOVEMENTCOMPONENT;

	PlayerMovementComponent();

	virtual void initComponent();

	virtual void handleInput();
};

