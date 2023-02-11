#pragma once
#include "../core/GameObject.h"
#include "Component.h"
#include "Transform.h"




class PlayerMovementComponent : public Component
{
private:
	Transform* transform;
	float playerSpeed = 0.001;

public:
	static const int id = _PLAYERMOVEMENTCOMPONENT;

	PlayerMovementComponent();

	virtual void initComponent();

	virtual void handleInput();

	void setPlayerSpeed(int newSpeed);

};

