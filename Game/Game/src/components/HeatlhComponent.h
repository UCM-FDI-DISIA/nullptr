#pragma once
#include "Component.h"

// Este componente sirve para manejar todos los eventos relacionados con la vida del objeto
// Como su muerte o su curación
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
