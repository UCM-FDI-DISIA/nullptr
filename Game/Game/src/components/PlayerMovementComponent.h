#pragma once
#include "../core/GameObject.h"
#include "Component.h"
#include "Transform.h"


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

