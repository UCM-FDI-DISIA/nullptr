#pragma once
#include "TentaclesPortalComponent.h"

class TentacleBehaviour: public Component {
private:
	Transform* tr;
	TentaclesPortalComponent* portals;
	int state;
	double timeOffset;
	float maxWitdh;
	bool orientation;

public:
	static const int id = _TENTACLE_BEHAVIOUR;
	TentacleBehaviour(TentaclesPortalComponent* tpc, bool mirror);
	virtual void initComponent();
	virtual void update();
};
