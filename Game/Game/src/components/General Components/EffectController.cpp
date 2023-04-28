#pragma once
#include "EffectController.h"
#include "../../core/SDLApplication.h"

EffectController::EffectController(Image* image) : image(image)
{
}

void EffectController::update()
{

	int r = 255, g = 255, b = 255, a = 255;
	
	for (auto& effect : currentEffects)
	{
		double second = fmod(effect.timer, 100.0);


		switch (effect.effect)
		{
		case E_BURNING:
			if (second < 33) {
				r = 255; g = 195; b = 0;
			}
			if (second > 33 && second < 66) {
				r = 255; g = 87; b = 51;
			}
			if (second > 66) {
				r = 255; g = 66; b = 51;
			}
			break;
		case E_CONFUSED:
				r = 129; g = 56; b = 231;
			break;
		case E_INVULN:
				a = 100;
			break;
		case E_DAMAGED:
				r = 255; g = 50; b = 50;
			break;
		default:
			break;
		}

		
		effect.timer -= SDLApplication::instance()->getDeltaTimeSeconds();

	}

	
	image->changeTint(r, g, b);
	image->changeAlpha(a);
	
	for (auto it = currentEffects.begin(); it != currentEffects.end();) {
		if (it->timer < 0) {
			it = currentEffects.erase(it);
		}
		else
			++it;
	}
	
	
	
}

void EffectController::startEffect(effectID effect, double duration)
{
	Effect ef;
	ef.effect = effect;
	ef.timer = duration;
	currentEffects.push_back(ef);
}




