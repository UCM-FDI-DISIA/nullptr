#pragma once
#include "../Component.h"
#include "../../core/SDLApplication.h"
class TentacleBehaviour: public Component
{
private:
	int originalX;
	int originalY;
	Transform* bossTransform;
	Transform* myTransform;
	float initTime;
	bool initCompleted;
	float rotationTime;
	bool rotationCompleted;
	float delayTime;
	bool delayCompleted;
	float elapsedTime;
	float maxWidth;
	bool isMirror;
public:
	static const int id = _TENTACLE_BEHAVIOUR;
	TentacleBehaviour(bool mirror);
	virtual void initComponent();
	virtual void update();
};
