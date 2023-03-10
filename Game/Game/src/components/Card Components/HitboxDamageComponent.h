#pragma once
#include "../Component.h"
#include "../General Components/ColliderComponent.h"
#include "../General Components/HealthComponent.h"
#include "../../gameObjects/GameObject.h"
#include <vector>
#include <unordered_set>

// Este componente maneja toda la lógica de las balas, como su interacción con otros objetos
class HitboxDamageComponent : public Component
{
private:
	int damage;
	bool destroy;
	bool knockback;
	unordered_set<GameObject*> hitRegistry;

public:
	static const int id = _HITBOX_DAMAGE_COMPONENT;

	HitboxDamageComponent(int dmg, bool dstry, bool knback) : damage(dmg), destroy(dstry), knockback(knback) {}

	// Función que se realiza cuando choca
	void initComponent() override{
		gObj->getComponent<ColliderComponent>()->addFunction(damageFunction());
	}

	CallBackCol damageFunction() {
		return [&](GameObject* trgt)
		{
			if (hitRegistry.count(trgt) == 0) {
				trgt->getComponent<HealthComponent>()->receiveDamage(damage);
				if (knockback) {
					Transform* tr = trgt->getComponent<Transform>();
					tr->setPos(tr->getPos() + tr->getVel() * -20);
				}
				if (destroy) gObj->setAlive(false);
				else hitRegistry.insert(trgt);
			}
		};
	}
};
