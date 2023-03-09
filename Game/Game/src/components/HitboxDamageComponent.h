#pragma once
#include "../Component.h"
#include "../General Components/ColliderComponent.h"
#include "../General Components/HealthComponent.h"
#include "../../gameObjects/GameObject.h"
#include <vector>

// Este componente maneja toda la lógica de las balas, como su interacción con otros objetos
class HitboxDamageComponent : public Component
{
private:
	int damage;
	bool destroy;
	bool knockback;

	CallBackCol damageFunction()
	{
		// Baja la vida del objetivo y se destruye
		return [&](GameObject* trgt) {
			trgt->getComponent<HealthComponent>()->receiveDamage(damage);
			if(destroy) gObj->setAlive(false); // Al colisionar, la bala se destruye
			if (knockback) {
				Transform* tr = trgt->getComponent<Transform>();
				tr->setPos(tr->getPos() + tr->getVel() * -20);
			}

		};
	}

public:
	static const int id = _HITBOX_DAMAGE_COMPONENT;

	HitboxDamageComponent(int dmg, bool dstry, bool knback) : damage(dmg), destroy(dstry), knockback(knback) {}

	// Función que se realiza cuando choca
	void initComponent() override{
		gObj->getComponent<ColliderComponent>()->addFunction(damageFunction());
	}
};
