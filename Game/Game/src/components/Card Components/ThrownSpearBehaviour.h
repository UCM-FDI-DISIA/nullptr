#pragma once
#include "../Component.h"
#include "../General Components/ColliderComponent.h"
#include "../General Components/HeatlhComponent.h"
#include "../../gameObjects/GameObject.h"
#include <vector>

// Este componente maneja toda la lógica de las balas, como su interacción con otros objetos
class ThrownSpearBehaviour :public Component
{
private:
	int damage;
public:
	static const int id = _BULLET_COMPONENT;
	// Recibe un vector de enemigos con los que debera colisionar la bala del player
	ThrownSpearBehaviour(int dmg)
	{
		damage = dmg;
	}
	CallBackCol spearAttack()
	{
		return [&](GameObject* gameObject)
		{
			gameObject->getComponent<HealthComponent>()->receiveDamage(damage);
			auto tr = gameObject->getComponent<Transform>();
			tr->setPos(tr->getPos() + tr->getVel() * -20);
			gObj->setAlive(false); // Al colisionar, la bala se destruye
		};
	}
};
