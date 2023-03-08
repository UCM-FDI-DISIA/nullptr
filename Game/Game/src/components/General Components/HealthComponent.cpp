#include "HealthComponent.h"
#include"../../gameObjects/GameObject.h"
#include "../../scenes/BattleScene.h"
#include "../Enemy components/RangeBehaviour.h"
#include "../Enemy components/MeleeBehaviour.h"

// Al construirse, adopta el gameObject y su manager como propios
// También define la vida máxima del objeto
HealthComponent::HealthComponent(int life, bool Player)
{
	maxLife = modifiedMaxLife = lifePoints = life;
	player = Player;
	invTime = 1000;
}
// Resta el daño a la vida actual y si baja de 0, mata al objeto
void HealthComponent::receiveDamage(int damage)
{
	// Si eres jugador, solo recibes daño si ha pasado el tiempo de invencibilidad
	if (time >= invTime) {
		lifePoints -= damage;
		cout << lifePoints <<endl;
		if (player) {
			time = 0;
			cout << "Invencible" << endl;
		}
	}
	if (lifePoints <= 0) die();
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

	lifePoints = lifePercent * modifiedMaxLife; // Aplica el porcentaje anterior como vida de la vida máxima actual
}