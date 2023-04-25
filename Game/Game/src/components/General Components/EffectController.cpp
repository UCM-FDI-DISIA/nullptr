#include "EffectController.h"
#include "../../core/SDLApplication.h"

EffectController::EffectController(Image* image) : image(image), timer(0), currentEffect(E_NONE)
{
}

void EffectController::update()
{
	if (currentEffect == E_CONFUSED)
	{

	}
	if (currentEffect == E_BURNING)
	{

	}
	if (currentEffect == E_INVULN)
	{
		double second = fmod(timer, 100);
		float blinkFactor = abs(second - 50);

		image->changeAlpha(255 - blinkFactor * 2);
	}

	if (currentEffect != E_NONE)
	{
		timer -= SDLApplication::instance()->getDeltaTimeSeconds();
	}
	
	if (timer < 0)
	{
		currentEffect = E_NONE;
	}
}

void EffectController::startEffect(effectID effect, double duration)
{
	currentEffect = effect;
	timer = duration;
}




