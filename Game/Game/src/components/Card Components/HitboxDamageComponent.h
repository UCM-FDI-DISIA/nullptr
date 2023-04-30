#pragma once
#include "../Component.h"
#include "../General Components/ColliderComponent.h"
#include "../General Components/HealthComponent.h"
#include "../../gameObjects/GameObject.h"
#include <vector>
#include <unordered_set>

class RitualAxeCard;
// Este componente maneja toda la lógica de las balas, como su interacción con otros objetos
class HitboxDamageComponent : public Component
{
private:
	float damage; //daño que causa
	bool destroy; //Si el objeto se destruye al colisionar
	RitualAxeCard* axe; //Si el ataque es del Hacha Ritual
	unordered_set<GameObject*> hitRegistry; //Set que registra los choques anteriores
	Vector2D parentData;

public:
	static const int id = _HITBOX_DAMAGE_COMPONENT;

	HitboxDamageComponent(float dmg, bool dstry, RitualAxeCard* axeC = nullptr, Vector2D parentData= VECTOR_ZERO) : damage(dmg), destroy(dstry), axe(axeC), parentData(parentData) {}

	// Se le añade al colider la funcion de daño
	void initComponent() override{
		gObj->getComponent<ColliderComponent>()->addFunction(damageFunction());
	}

	//Funcion que se llama al colisionar, causa daño al objeto con el que se ha colisionado
	CallBackCol damageFunction() {
		return [&](GameObject* trgt)
		{
			if (hitRegistry.count(trgt) == 0) {
				trgt->getComponent<HealthComponent>()->receiveDamage(damage, axe, parentData, gObj->getComponent<Transform>()->getVel());
				if (destroy) gObj->setAlive(false);
				else hitRegistry.insert(trgt);
			}
		};
	}
};
