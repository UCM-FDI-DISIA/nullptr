#pragma once
#include "../Component.h"
#include "../General Components/ColliderComponent.h"
#include <vector>

// Este componente maneja el comportamiento de los objetos Slash creados, 
class ConfuseBehaviour : public Component {

private:
	float duration;
	vector<GameObject*>* target;
	vector<bool> hitRegistry;
public:
	static const int id = _SWORD_BEHAVIOUR;
	// Recibe un vector de enemigos con los que debera colisionar la bala del player y crea el vector de colisionados del mismo tamaño
	ConfuseBehaviour(float drt, vector<GameObject*>* Target)
	{
		target = Target;
		hitRegistry.assign((*Target).size(), false);
		duration = drt;
	}

	virtual void update()
	{
		// cleon says: ejem...
		for (int i = 0; i < target->size(); i++) {
			// Comprueba si ha chocado con el objetivo
			if (gObj->getComponent<ColliderComponent>()->
				hasCollided((*target)[i]->getComponent<Transform>())) {
				//Comprueba si ya ha colisionado anteriormente con el mismo objeto
				if (!hitRegistry[i]) {
					cout << "hizo damages" << endl;
					//Confunde al oponente
					//(*target)[i]->getComponent<StatusComponent>()->confuse(duration);
					hitRegistry[i] = true;
				}

			}
		}
	}
};