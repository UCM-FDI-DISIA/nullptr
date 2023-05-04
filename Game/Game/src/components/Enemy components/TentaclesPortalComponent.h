#pragma once
#include "../General Components/Transform.h"

class TentaclesPortalComponent : public Component {
	enum ClockState {
		INITIAL, SPREAD, MOVE, AWAIT
	};

private:
	Transform* tr;
	Transform* boss;
	ClockState state;
	double timeOffset;

	Transform* tentIzq;
	Transform* tentDer;
	GameObject* ti;
	GameObject* td;

public:
	static const int id = _TENTACLES_PORTAL_;
	TentaclesPortalComponent(Transform* b);
	virtual void initComponent();
	virtual void update();
	void calculatePos();
};