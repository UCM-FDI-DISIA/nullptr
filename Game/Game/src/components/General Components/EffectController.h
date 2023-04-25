#include "../Component.h"
#include "Image.h"


class EffectController : public Component {
public:
	enum effectID
	{
		E_BURNING,
		E_CONFUSED,
		E_INVULN,
		E_NONE
	};
private:

	Image* image;
	double timer;
	effectID currentEffect;

public:

	static const int id = _EFFECT_CONTROLLER;


	EffectController(Image* image);

	void update();

	void startEffect(effectID effect, double duration);

};