#include "HealthComponent.h"
#include"../../gameObjects/GameObject.h"
#include "../../scenes/BattleScene.h"
#include "../Enemy components/RangeBehaviour.h"
#include "../Enemy components/MeleeBehaviour.h"

// Al construirse, adopta el gameObject y su manager como propios
// Tambi�n define la vida m�xima del objeto
HealthComponent::HealthComponent(int life, bool Invincibility)
{
	maxLife = modifiedMaxLife = lifePoints = life;
	invincibility = Invincibility;
	invTime = 1000;
}

// Resta el da�o a la vida actual y si baja de 0, mata al objeto
void HealthComponent::receiveDamage(int damage)
{
	// Si eres jugador, solo recibes da�o si ha pasado el tiempo de invencibilidad
	if (time >= invTime) {
		lifePoints -= damage;
		cout << lifePoints <<endl;
		if (lifePoints <= 0) die();
		else {
			if (gObj->getComponent<PlayerMovementComponent>() != nullptr) { 
				auto sc = dynamic_cast<BattleScene*>(gStt); 
				sc->OnPlayerDamage(lifePoints); 
			}
		}
		if (invincibility) {
			time = 0;
			cout << "Invencible" << endl;
		}
	}
}

void HealthComponent::update()
{
	time += SDLApplication::instance()->getDeltaTime();
}

// Cura al objeto el valor puesto
void HealthComponent::heal(int heal)
{
	if (lifePoints + heal <= modifiedMaxLife) lifePoints += heal;
	else lifePoints = modifiedMaxLife;
}

// Al llegar la vida a 0, el objetose dispone a morir
// En el caso del jugador, termina la partida
void HealthComponent::die()
{
	auto sc = dynamic_cast<BattleScene*>(gStt);
	if (gObj->hasComponent<CardComponent>()) {
		sc->OnPlayerDies();
	}
	gObj->setAlive(false);
}

// Multiplica la vida maxima, que nunca cambia, por el multiplicador dado
void HealthComponent::multiplyLife(double multiplier)
{
	float lifePercent = lifePoints / modifiedMaxLife; // Saca el porcentaje de la vida actual

	modifiedMaxLife = maxLife * multiplier; // Modifica la vida maxima actual

	lifePoints = lifePercent * modifiedMaxLife; // Aplica el porcentaje anterior como vida de la vida m�xima actual
}