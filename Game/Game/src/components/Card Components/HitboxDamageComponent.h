#pragma once
#include "HitboxComponent.h"
#include "../General Components/ColliderComponent.h"
#include "../General Components/HealthComponent.h"
#include "../../gameObjects/GameObject.h"
#include <vector>

// Este componente maneja toda la lógica de las balas, como su interacción con otros objetos
class HitboxDamageComponent : public HitboxComponent
{
private:
	int damage;
	bool destroy;
	bool knockback;

public:
	static const int id = _HITBOX_DAMAGE_COMPONENT;

	HitboxDamageComponent(int dmg, bool dstry, bool knback) : damage(dmg), destroy(dstry), knockback(knback) {}

	// Función que se realiza cuando choca
	void initComponent() override{
		gObj->getComponent<ColliderComponent>()->addFunction(this);
	}

	void hitboxFunction(GameObject* trgt) override
	{
		trgt->getComponent<HealthComponent>()->receiveDamage(damage);
		if (destroy) gObj->setAlive(false); // Al colisionar, la bala se destruye
		if (knockback) {
			Transform* tr = trgt->getComponent<Transform>();
			tr->setPos(tr->getPos() + tr->getVel() * -20);
		}
	}
};
