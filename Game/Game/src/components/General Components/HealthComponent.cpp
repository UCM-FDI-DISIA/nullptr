#include "HealthComponent.h"
#include"../../gameObjects/GameObject.h"
#include "../../scenes/BattleScene.h"
#include "../Enemy components/RangeBehaviour.h"
#include "../Enemy components/MeleeBehaviour.h"
#include "../Enemy components/OnDeath.h"
#include "../../gameObjects/Card Objects/Cards.h"

// Al construirse, adopta el gameObject y su manager como propios
// Tambi�n define la vida m�xima del objeto
HealthComponent::HealthComponent(int life, bool Invincibility) :
	maxLife(life), modifiedMaxLife(life), lifePoints(life), 
	invincibility(Invincibility), invTime(0),
	onDeath(nullptr) {}

// Resta el da�o a la vida actual y si baja de 0, mata al objeto
void HealthComponent::receiveDamage(int damage, RitualAxeCard* axe)
{
	// Si eres jugador, solo recibes da�o si ha pasado el tiempo de invencibilidad
	if (invTime <= 0) {
		lifePoints -= damage;
		cout << lifePoints << endl;

		// Si se trata del Player, actualiza su barra de vida
		if (gObj->getComponent<PlayerMovementComponent>() != nullptr) {
			auto sc = dynamic_cast<BattleScene*>(gStt);
			sc->OnPlayerDamage(lifePoints);
		}

		if (lifePoints <= 0) {
			die();
			if (axe != nullptr) axe->enemieKilled();
		} 
		
		if (invincibility) {
			invTime = 0.5;
			cout << "Invencible" << endl;
		}
	}
}
void HealthComponent::setInvencibility(float time)
{
	if (invincibility) invTime = time;
}

void HealthComponent::initComponent() {
	onDeath = gObj->getComponent<OnDeath>();
}

void HealthComponent::update()
{
	if (invTime > 0) invTime -= SDLApplication::instance()->getDeltaTimeSeconds();
}

// Cura al objeto el valor puesto
void HealthComponent::heal(int heal)
{
	if (lifePoints + heal <= modifiedMaxLife) 
		lifePoints += heal;
	else lifePoints = modifiedMaxLife;
	dynamic_cast<BattleScene*>(gStt)->OnPlayerDamage(lifePoints);
}

// Al llegar la vida a 0, el objeto se dispone a morir
void HealthComponent::die()
{
	if (onDeath != nullptr) {
		onDeath->death();
		gObj->setAlive(false);
	}
}

// Multiplica la vida maxima, que nunca cambia, por el multiplicador dado
void HealthComponent::multiplyLife(double multiplier)
{
	float lifePercent = lifePoints / modifiedMaxLife; // Saca el porcentaje de la vida actual

	modifiedMaxLife = maxLife * multiplier; // Modifica la vida maxima actual

	lifePoints = lifePercent * modifiedMaxLife; // Aplica el porcentaje anterior como vida de la vida m�xima actual
}