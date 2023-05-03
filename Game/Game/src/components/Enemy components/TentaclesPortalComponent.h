#pragma once
#include "../General Components/Transform.h"

class TentaclesPortalComponent : public Component {
private:
	Transform* tr;
	Transform* boss;
	int state;
	bool startRotation;
	double timeOffset;

	Transform* tentIzq;
	Transform* tentDer;
	GameObject* ti;
	GameObject* td;

public:
	static const int id = _TENTACLES_PORTAL_;
	TentaclesPortalComponent(Transform* b);
	void setStartRotation(bool value) { startRotation = value; }
	virtual void initComponent();
	virtual void update();
	void calculatePos();
};