#pragma once
#include "EffectController.h"
#include "../../core/SDLApplication.h"

EffectController::EffectController(Image* image) : image(image), timer(0), currentEffect(E_NONE)
{
}

void EffectController::update()
{
	
	double second = fmod(timer, 100);
	switch (currentEffect)
	{
	case E_BURNING:
		if (second < 33) {
			image->changeTint(255, 195, 0);
		}else if (second < 66) {
			image->changeTint(255, 87, 51);
		}else {
			image->changeTint(255, 66, 51);
		}
		break;
	case E_CONFUSED:
		break;
	case E_INVULN:
		image->changeAlpha(255 - abs(second - 50) * 2);
		break;
	case E_NONE:
		image->changeAlpha(255);
		image->changeTint(255,255,255);
		break;
	default:
		break;
	}

	if (timer > 0)
		timer -= SDLApplication::instance()->getDeltaTimeSeconds();
	
	
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




