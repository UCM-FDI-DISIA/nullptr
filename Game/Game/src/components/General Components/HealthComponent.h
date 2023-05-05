#pragma once
#include "../Component.h"

// Este componente sirve para manejar todos los eventos relacionados con la vida del objeto
// Como su muerte o su curación
class OnDeath;
class RitualAxeCard;
class EffectController;
class Transform;
class HealthComponent : public Component {
private:
	int lifePoints;
	int maxLife;
	int modifiedMaxLife;
	bool invincibility;
	float invTime;
	OnDeath* onDeath;
	EffectController* eController;
	Transform* transform;
	SoundEffect* hitSound;
	SoundEffect* healSound;
	bool knockBack;

public:
	static const int id = _HEALTH;
	HealthComponent(int Maxlife, bool invincibility = false);
	//Delete del padre
	void receiveDamage(float damage, RitualAxeCard* axe = nullptr, Vector2D damageOrigin=VECTOR_ZERO, Vector2D damageVel=Vector2D());
	void setInvencibility(float time);
	float getInvencibility();
	virtual void initComponent();
	virtual void update();
	void heal(int heal);
	void die();
	// Devuelve el valor actual de la vida
	inline int getLife() { return lifePoints; }
	void multiplyLife(double multiplier);
	void setKnockBack(bool value) { knockBack = value; }
};
