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
	
		#ifdef _DEBUG
			std::cout << second << "\n";
		#endif // DEBUG

		switch (effect.effect)
		{
		case E_DAMAGED:
				r = 255; g = 50; b = 50;
			break;
		case E_BURNING:
			if (second < 0.33) {
				r = 255; g = 195; b = 0;
			}
			else if (second > 0.33 && second < 0.66) {
				r = 255; g = 97; b = 51;
			}
			else if (second > 0.66) {
				r = 255; g = 66; b = 51;
			}
			break;
		case E_CONFUSED:
				r = 129; g = 56; b = 231;
			break;
		case E_INVULN:
			if (second > 0.75 || second > 0.25  && second < 0.5)
				a = 0;
			else a = 255;
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

	if (effect == E_DAMAGED)
	{
		//Buscar si hay un efecto de quemado
		bool found = false;
		auto it = currentEffects.begin();
		while (it != currentEffects.end() && !found)
		{
			if (it->effect == E_BURNING)
			{
				found = true;
			}
			it++;
		}
		if (found)
			return;
		
	}

	Effect ef;
	ef.effect = effect;
	ef.timer = duration;

	currentEffects.push_back(ef);
}




