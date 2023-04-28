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

	struct Effect {
		effectID effect;
		double timer;
	};
class EffectController : public Component {
public:
private:

	Image* image = nullptr;
	std::vector<Effect> currentEffects;

public:

	static const int id = _EFFECT_CONTROLLER;

	EffectController(Image* image);

	void update();

	void startEffect(effectID effect, double duration);

};