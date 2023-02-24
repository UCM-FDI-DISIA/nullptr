#pragma once
#include "Component.h"
#include "ColliderComponent.h"
#include "HeatlhComponent.h"
#include <vector>

// Este componente maneja toda la lógica de las balas, como su interacción con otros objetos
class BulletBehavior:public Component
{
private:
	int damage;
	vector<GameObject*>* target; // cleon says: adiós, gatitos. adiós. // E Rafa says: probablemente ni nos haga falta
public:
	static const int id = _BULLET_COMPONENT;
	// Recibe un player que se mete en el vector target, que hace las veces de matriz de colision
	BulletBehavior(int dmg, GameObject* Target) {
		target = new vector<GameObject*>();
		target->push_back(Target);
		damage = dmg;
	}
	// Recibe un vector de enemigos con los que debera colisionar la bala del player
	BulletBehavior(int dmg, vector<GameObject*>*Target)
	{
		target = Target;
		damage = dmg;
	}

	virtual void update()
	{
		// cleon says: 1º: usad loops modernos (C++11).
		// no uséis "vector" como un array.
		//E Rafa says : probablemente ni nos haga falta
		// Comprueba si ha chocado con el objetivo y, si lo hace, le baja vidaç
		for (int i = 0; i < target->size(); i++) {
			if (gObj->getComponent<ColliderComponent>()->
				hasCollided((* target)[i]->getComponent<Transform>())) {
				(* target)[i]->getComponent<HealthComponent>()->receiveDamage(damage);
				gObj->setAlive(false); // Al colisionar, la bala se destruye
			}
		}
	}
};
