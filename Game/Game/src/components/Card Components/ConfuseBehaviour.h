#pragma once
#include "../Component.h"
#include "../General Components/ColliderComponent.h"
#include <vector>

// Este componente maneja el comportamiento de los objetos Slash creados, 
class ConfuseBehaviour : public Component {

private:
	float duration;
	grpId myGroup;
	vector<bool> hitRegistry;
	int actualObject;
public:
	static const int id = _SWORD_BEHAVIOUR;
	// Recibe un vector de enemigos con los que debera colisionar la bala del player y crea el vector de colisionados del mismo tamaño
	ConfuseBehaviour(float drt, grpId group)
	{
		myGroup = group;
		duration = drt;
		actualObject = 0;
	}
	virtual void initComponent()
	{
		hitRegistry.assign(gStt->getEntitiesByGroup(myGroup).size(), false);
	}

	CallBackCol confuseAttack()
	{
		return [&](GameObject* gameObject)
		{
			//Comprueba si ya ha colisionado anteriormente con el mismo objeto
			if (!hitRegistry[actualObject]) {
				cout << "hizo damages" << endl;
				//Confunde al oponente
				//(*target)[i]->getComponent<StatusComponent>()->confuse(duration);
				hitRegistry[actualObject] = true;
			}
			actualObject++;
			if (actualObject >= hitRegistry.size()) actualObject = 0;
		};
	}
};