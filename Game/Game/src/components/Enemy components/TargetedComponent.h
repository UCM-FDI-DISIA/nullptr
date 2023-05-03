#pragma once
#include "../General Components/Transform.h"
class TargetedComponent : public Component {
private:
	Transform* tr;
	Transform* pltr;
	Transform* bossTr;
	int maxWidth, state;
	double timeOffset;

public:
	static const int id = _TARGETED_BEHAVIOUR;
	TargetedComponent(Transform* p, Transform* b);
	void calculatePos();
	virtual void initComponent();
	virtual void update();
};