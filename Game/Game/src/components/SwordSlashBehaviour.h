#pragma once
#pragma once
#include "Component.h"
#include "ColliderComponent.h"
#include "HeatlhComponent.h"
#include <vector>

// Este componente maneja el comportamiento de los objetos Slash creados, 
class SwordSlashBehaviour : public Component {

private:
	int damage;
	vector<GameObject*>* target;
	vector<bool> hitRegistry;
public:
	static const int id = _SWORD_BEHAVIOUR;
	// Recibe un player que se mete en el vector target, que hace las veces de matriz de colision y crea el array que determina si se ha colisionado con ese objeto o no.
	SwordSlashBehaviour(int dmg, GameObject* Target) {
		target = new vector<GameObject*>();
		target->push_back(Target);
		hitRegistry.assign(1, false);
		damage = dmg;
	}
	// Recibe un vector de enemigos con los que debera colisionar la bala del player y crea el vector de colisionados del mismo tamaño
	SwordSlashBehaviour(int dmg, vector<GameObject*>*Target)
	{
		target = Target;
		hitRegistry.assign((*Target).size(), false);
		damage = dmg;
	}

	virtual void update()
	{
		for (int i = 0; i < target->size(); i++) {
		// Comprueba si ha chocado con el objetivo
			if (gObj->getComponent<ColliderComponent>()->
				hasCollided((*target)[i]->getComponent<Transform>())) {
				//Comprueba si ya ha colisionado anteriormente con el mismo objeto
 				if (!hitRegistry[i]) {
					cout << "hizo damages" << endl;
					//Hace el daño y lo añade a la lista de ya colisionados
					(*target)[i]->getComponent<HealthComponent>()->receiveDamage(damage);
					hitRegistry[i] = true;
				}
				
			}
		}
	}
};