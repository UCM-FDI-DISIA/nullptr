#pragma once
#include "../Component.h"
#include"../General Components/Transform.h"
#include "../../scenes/GameState.h"
#include "../../core/SDLApplication.h"
class EterBehaviour: public Component
{
private:
	Transform* myTransform;
	float speeding;
	float floorTime;
	float elapsedTime;
	Vector2D dest;
	Vector2D dir;
public:
	static const int id = _ETER;
	EterBehaviour(float groundTime);
	virtual void initComponent();
	virtual void update();
};