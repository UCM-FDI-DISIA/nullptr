#pragma once
#include "../Component.h"
#include"../General Components/Transform.h"
#include "../../scenes/GameState.h"
#include "../../core/SDLApplication.h"
class EterBehaviour: public Component
{
private:
	Transform* myTransform;
	Transform* plyr;
	float speeding;
	float floorTime;
	float elapsedTime;
	Vector2D dest;
	Vector2D dir;
	SoundEffect* etherPickSound;
public:
	static const int id = _ETER;
	EterBehaviour(float groundTime,Transform* player);
	virtual void initComponent();
	virtual void update();
};