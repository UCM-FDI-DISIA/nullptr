#pragma once
#include "../Component.h"

// Este componente sirve para manejar todos los eventos relacionados con la vida del objeto
// Como su muerte o su curación
class OnDeath;
class RitualAxeCard;
class EffectController;
class HealthComponent : public Component {
private:
	int lifePoints;
	int maxLife;
	int modifiedMaxLife;
	bool invincibility;
	float invTime;
	OnDeath* onDeath;
	EffectController* eController;
	
public:
	static const int id = _HEALTH;
	HealthComponent(int Maxlife, bool invincibility = false);
	//Delete del padre
	void receiveDamage(float damage, RitualAxeCard* axe = nullptr);
	void setInvencibility(float time);
	virtual void initComponent();
	virtual void update();
	void heal(int heal);
	void die();
	// Devuelve el valor actual de la vida
	inline int getLife() { return lifePoints; }
	void multiplyLife(double multiplier);
};
