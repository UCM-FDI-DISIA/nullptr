#pragma once
#include "../../gameObjects/GameObject.h"
#include "../Component.h"
#include "../General Components/Transform.h"
#include "../../core/GameControl.h"

class PlayerMovementComponent : public Component
{
private:
	Transform* transform;
	Vector2D moveDir;
	float dashDuration;
	float playerSpeed = PLAYER_SPEED;
	GameControl& gmCtrl_;
public:
	static const int id = _PLAYERMOVEMENTCOMPONENT;

	PlayerMovementComponent();

	void initComponent() override;

	void handleInput() override;

	void update() override;
	void setDirection(Vector2D dir);

	void setPlayerSpeed(float newSpeed);

	void dash(Vector2D direction);

};

