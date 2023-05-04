#pragma once
#include "HitboxStatusComponent.h"
#include "../General Components/ColliderComponent.h"
#include "../../gameObjects/GameObject.h"
#include <vector>
#include "../General Components/StatusComponent.h"


// Este componente maneja el comportamiento de los objetos Slash creados, 
class HitboxStatusComponent : public Component {
private:
	float duration;
	StatusComponent::status status;
	unordered_set<GameObject*> hitRegistry; //Set que registra los choques anteriores

public:

	static const int id = _HITBOX_STATUS_COMPONENT;
	// Recibe un grupo de objetos con el que debe colisionar la hitbox, y una duraci�n y un estado que debe aplicar
	HitboxStatusComponent(StatusComponent::status stts, float drt) : duration(drt), status(stts)	{}

	inline void initComponent() override
	{
		gObj->getComponent<ColliderComponent>()->addFunction(statusFunction());
	}

	CallBackCol statusFunction() {
		return [&](GameObject* trgt)
		{			
			if (hitRegistry.count(trgt) == 0 && trgt->getComponent<StatusComponent>()) {
				trgt->getComponent<StatusComponent>()->applyStatus(status, duration);
				hitRegistry.insert(trgt);
			}
		};
	}
};