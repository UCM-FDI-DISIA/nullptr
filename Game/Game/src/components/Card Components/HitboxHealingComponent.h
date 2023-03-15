#pragma once
#include "HitboxStatusComponent.h"
#include "../General Components/HealthComponent.h"
#include "../../gameObjects/GameObject.h"
#include "../../core/SDLApplication.h"
#include <vector>


// Este componente maneja el comportamiento de los objetos Slash creados, 
class HitboxHealingComponent : public Component {
private:
	int healing;
	float cooldown;
	unordered_map<GameObject*,float> healCooldown; //Set que registra los choques anteriores


public:
	static const int id = _HITBOX_STATUS_COMPONENT;
	// Recibe un grupo de objetos con el que debe colisionar la hitbox, y una duración y un estado que debe aplicar
	HitboxHealingComponent(int heal, float cd) : healing(heal), cooldown(cd) {}

	inline void initComponent() override
	{
		gObj->getComponent<ColliderComponent>()->addFunction(healingFunction());
	}

	CallBackCol healingFunction() {
		return [&](GameObject* trgt)
		{		
			if (healCooldown.count(trgt) == 0 || healCooldown[trgt] <= 0) {
				trgt->getComponent<HealthComponent>()->heal(healing);
				healCooldown[trgt] = cooldown;
			}
			else {
				healCooldown[trgt] -= SDLApplication::instance()->getDeltaTimeSeconds();
			}
		};
	}
};