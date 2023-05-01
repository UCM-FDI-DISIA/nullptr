#include "HealthComponent.h"
#include "EffectController.h"
#include "Transform.h"
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
	onDeath(nullptr){}

// Resta el da�o a la vida actual y si baja de 0, mata al objeto
void HealthComponent::receiveDamage(float damage, RitualAxeCard* axe, Vector2D damageOrigin, Vector2D damageVel)
{
	// Si eres jugador, solo recibes da�o si ha pasado el tiempo de invencibilidad
	if (invTime <= 0) {
		lifePoints -= damage;
		if (lifePoints > 0 && gObj->hasComponent<EffectController>()) {
			if (eController == nullptr) eController = gObj->getComponent<EffectController>();
			eController->startEffect(E_DAMAGED, 0.5);
		}
		// Si se trata del Player, actualiza su barra de vida
		if (gObj->getComponent<PlayerMovementComponent>() != nullptr) {
			auto sc = dynamic_cast<BattleScene*>(gStt);
			sc->OnPlayerDamage(lifePoints);
			sc->getTracker()->onPlayerDamage(damage);
		}

		if (lifePoints <= 0) {
			die();
			if (axe != nullptr) axe->enemieKilled();
		}
		else if(invTime <= 0) {
			//Si la hitbox es estática es un ataque cuerpo a cuerpo, si no es una bala
			//En el primer caso tomamos en cuenta el objeto que lo origina para calcular la direccion
			//En el segundo tomamos en cuenta la velocidad de la bala
			if (damageVel.magnitude()!=Vector2D().magnitude())
				transform->push(damageVel.normalize()*PUSH_STRENGTH);
			else {
				Vector2D vel = transform->getPos() - damageOrigin;
				transform->push((vel.normalize()) * PUSH_STRENGTH);
			}
			//Reproduce el sonido de golpe
			Mix_PlayChannelTimed(-1, hitSound->getChunk(), 0, -1);
			
		}
		if (invincibility) {
			invTime = 1.5;

			if ( lifePoints > 0 && gObj->hasComponent<EffectController>()) {
				if (eController == nullptr) eController = gObj->getComponent<EffectController>();
				eController->startEffect(E_INVULN, 1.25);
			}
		}
		else
		{
				
			if (gObj->hasComponent<EffectController>()) {
				if (eController == nullptr) eController = gObj->getComponent<EffectController>();
				eController->startEffect(E_DAMAGED, 0.25);
			}
		}
	}
}
void HealthComponent::setInvencibility(float time)
{
	if (invincibility) {
		invTime = time;
		if (gObj->hasComponent<EffectController>()) {
			if (eController == nullptr) eController = gObj->getComponent<EffectController>();
			eController->startEffect(E_INVULN, time);
		}

	}
}

void HealthComponent::initComponent() {
	transform = gObj->getComponent<Transform>();
	eController = gObj->getComponent<EffectController>();
	onDeath = gObj->getComponent<OnDeath>();
	if (dynamic_cast<MeleeEnemy*>(gObj)) {
		hitSound = &sdlutils().soundEffects().at(MELEE_HIT_SOUND);
	}
	else if (dynamic_cast<RangedEnemy*>(gObj)) {
		hitSound = &sdlutils().soundEffects().at(RANGED_HIT_SOUND);
	}
	else if (dynamic_cast<TankEnemy*>(gObj)) {
		hitSound = &sdlutils().soundEffects().at(TANK_HIT_SOUND);
	}
	else if (dynamic_cast<Player*>(gObj)) {
		hitSound = &sdlutils().soundEffects().at(PLAYER_HIT_SOUND);
	}
	else if (dynamic_cast<AssasinEnemy*>(gObj)) {
		hitSound = &sdlutils().soundEffects().at(TANK_HIT_SOUND);
	}
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

	auto sc = dynamic_cast<BattleScene*>(gStt);
	if (gObj->hasComponent<CardComponent>()) {
		sc->OnPlayerDies();
	}
}

// Multiplica la vida maxima, que nunca cambia, por el multiplicador dado
void HealthComponent::multiplyLife(double multiplier)
{
	float lifePercent = lifePoints / modifiedMaxLife; // Saca el porcentaje de la vida actual

	modifiedMaxLife = maxLife * multiplier; // Modifica la vida maxima actual

	lifePoints = lifePercent * modifiedMaxLife; // Aplica el porcentaje anterior como vida de la vida m�xima actual
}