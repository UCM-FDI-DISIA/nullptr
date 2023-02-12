#pragma once
#include "Component.h"
class HealthComponent : public Component {
private:
	int lifePoints;
	int maxLife;
	int modifiedMaxLife;
public:
	static const int id = _HEALTH;
	HealthComponent(int Maxlife);
	//Delete del padre
	void receiveDamage(int damage);
	void heal(int heal);
	void die();
	int getLife();
	void multiplyLife(double multiplier);
	/*void timeDamage()*/
};
