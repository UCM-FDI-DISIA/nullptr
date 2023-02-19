#include "HeatlhComponent.h"
#include"../core/GameObject.h"
#include "../scenes/BattleScene.h"

// Al construirse, adopta el gameObject y su manager como propios
// También define la vida máxima del objeto
HealthComponent::HealthComponent(int life)
{
	maxLife = modifiedMaxLife = lifePoints = life;
}
// Resta el daño a la vida actual y si baja de 0, mata al objeto
void HealthComponent::receiveDamage(int damage)
{
	cout << "ouch" << endl;
	lifePoints -= damage;
	if (lifePoints <= 0) die();
}
// Cura al objeto el valor puesto
void HealthComponent::heal(int heal)
{
	if (lifePoints + heal <= modifiedMaxLife) lifePoints += heal;
	else lifePoints = modifiedMaxLife;
}
void HealthComponent::die()
{
	gObj->setAlive(false);
	if (gObj->hasComponent<CardComponent>()) {
		auto sc = dynamic_cast<BattleScene*>(gStt);
		sc->OnPlayerDies();
	}
	lifePoints = modifiedMaxLife;
}
// Devuelve el valor actual de la vida
int HealthComponent::getLife()
{
	return lifePoints;
}
// Multiplica la vida maxima, que nunca cambia, por el multiplicador dado
void HealthComponent::multiplyLife(double multiplier)
{
	float lifePercent = lifePoints / modifiedMaxLife; // Saca el porcentaje de la vida actual

	modifiedMaxLife = maxLife * multiplier; // Modifica la vida maxima actual

	lifePoints = lifePercent * modifiedMaxLife; // Aplica el porcentaje anterior como vida de la vida máxima actual
}