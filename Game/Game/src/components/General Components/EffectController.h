#pragma once
#include "../Component.h"
#include "Image.h"


	enum effectID
	{
		E_BURNING,
		E_CONFUSED,
		E_INVULN,
		E_DAMAGED,
		E_NONE
	};
class EffectController : public Component {
public:
private:

	Image* image = nullptr;
	double timer = 0.0;
	effectID currentEffect = E_NONE;

public:

	static const int id = _EFFECT_CONTROLLER;

	void initComponent() override;
	void update() override;

	void startEffect(effectID effect, double duration);

};