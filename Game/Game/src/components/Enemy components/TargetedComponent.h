#pragma once
#include "../Component.h"
#include "../../core/SDLApplication.h"
class TargetedComponent : public Component
{
private:
	int originalX;
	int originalY;
	Vector2D lastPlayerTransform;
	Transform* playerTransform;
	Transform* myTransform;
	float initTime;
	bool initCompleted;
	float delayTime;
	bool delayCompleted;
	float elapsedTime;
	float maxWidth;
	float actualRot;
public:
	static const int id = _TARGETED_BEHAVIOUR;
	TargetedComponent(Transform* bosTr);
	virtual void initComponent();
	virtual void update();
};