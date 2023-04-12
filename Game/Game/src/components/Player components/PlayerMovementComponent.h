#pragma once
#include "../../gameObjects/GameObject.h"
#include "../Component.h"
#include "../General Components/Transform.h"

class PlayerMovementComponent : public Component
{
private:
	Transform* transform;
	Vector2D moveDir;
	float dashDuration;
	float playerSpeed = PLAYER_SPEED;

public:
	static const int id = _PLAYERMOVEMENTCOMPONENT;

	PlayerMovementComponent();

	void initComponent() override;

	void handleInput() override;

	void update() override;

	void setPlayerSpeed(float newSpeed);

	void dash(Vector2D direction);

};

