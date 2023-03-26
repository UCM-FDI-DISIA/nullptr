#pragma once
#include "../../gameObjects/GameObject.h"
#include "../Component.h"
#include "../General Components/Transform.h"

class PlayerMovementComponent : public Component
{
private:
	Transform* transform;
	float playerSpeed = PLAYER_SPEED;

public:
	static const int id = _PLAYERMOVEMENTCOMPONENT;

	PlayerMovementComponent();

	virtual void initComponent();

	virtual void handleInput();

	void setPlayerSpeed(float newSpeed);

};

