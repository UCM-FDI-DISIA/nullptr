#pragma once
#include "Component.h"
class HealthComponent : public Component {
private:
	int lifePoints;
	int maxLife;
	int modifiedMaxLife;
public:
	HealthComponent(Manager* mngr_, GameObject* gameObject, int Maxlife);
	//Delete del padre
	void receiveDamage(int damage);
	void heal(int heal);
	void die();
	int getLife();
	void setLife(double multiplier);
	/*void timeDamage()*/
};
