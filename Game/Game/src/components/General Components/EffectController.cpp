#pragma once
#include "EffectController.h"
#include "../../core/SDLApplication.h"

void EffectController::initComponent() {
	image = gObj->getComponent<Image>();
}

void EffectController::update()
{

	int r = 255, g = 255, b = 255, a = 255;
	
	for (auto& effect : currentEffects)
	{
		double second = fmod(effect.timer, 1.0);
		std::cout << second << "\n";

		switch (effect.effect)
		{
		case E_BURNING:
			if (second < .033) {
				r = 255; g = 195; b = 0;
			}
			if (second > .033 && second < .066) {
				r = 255; g = 87; b = 51;
			}
			if (second > .066) {
				r = 255; g = 66; b = 51;
			}
			break;
		case E_CONFUSED:
				r = 129; g = 56; b = 231;
			break;
		case E_INVULN:
			if (second < 0.05)
				a = 100;
			else a = 150;
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




