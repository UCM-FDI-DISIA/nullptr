#pragma once
#include "../../gameObjects/GameObject.h"
#include "../Component.h"
#include "../General Components/Transform.h"
#include "../../core/GameControl.h"

class PlayerMovementComponent : public Component
{
private:
	Transform* transform;
	float playerSpeed = PLAYER_SPEED;
	GameControl& gmCtrl_;
public:
	static const int id = _PLAYERMOVEMENTCOMPONENT;

	PlayerMovementComponent();

	virtual void initComponent();

	void setDirection(Vector2D dir);

	void setPlayerSpeed(float newSpeed);

};

