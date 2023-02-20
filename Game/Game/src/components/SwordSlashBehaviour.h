#pragma once
#pragma once
#include "Component.h"
#include "ColliderComponent.h"
#include "HeatlhComponent.h"
#include <vector>

class SwordSlashBehaviour : public Component {

private:
	int damage;
	vector<GameObject*> target;
	vector<bool> hitRegistry;
public:
	static const int id = _SWORD_BEHAVIOUR;

	SwordSlashBehaviour(int dmg, GameObject* Target) {
		target.push_back(Target);
		hitRegistry.assign(1, false);
		damage = dmg;
	}
	SwordSlashBehaviour(int dmg, vector<GameObject*>Target)
	{
		target = Target;
		hitRegistry.assign(Target.size(), false);
		damage = dmg;
	}

	virtual void update()
	{
		for (int i = 0; i < target.size(); i++) {
		// Comprueba si ha chocado con el objetivo
			if (gObj->getComponent<ColliderComponent>()->
				hasCollided(target[i]->getComponent<Transform>())) {
 				if (!hitRegistry[i]) {
					cout << "hizo damages" << endl;
					target[i]->getComponent<HealthComponent>()->receiveDamage(damage);
					hitRegistry[i] = true;
				}
				
			}
		}
	}
};