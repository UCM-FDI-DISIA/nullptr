#include "TankBehaviour.h"

// Constructora
TankBehaviour::TankBehaviour(float spd, int dmg, float stop, float attack, Player* plyr) : EnemyBehaviour(spd, dmg, stop, attack, plyr), transform(nullptr), attacking(false), attacked(false), chargingAttack(false),  stop(stopTime), attackingTime(TANK_ATTACK_TIME) {}

void TankBehaviour::initComponent() {
	pos = gObj->getComponent<Transform>();
	// Establece la velocidad
	pos->setVel(Vector2D(0, speed));
	
	// Rota hacia la direccion del jugador
	pos->lookAt(playerPos->getPos());
}

void TankBehaviour::update() {
	
	// Si llega a estar a X distancia del jugador y no esta atacando...
	if (!attacking&& pos->getDistance(playerPos->getPos()) <= TANK_ATTACK_DISTANCE ) {
		//Empezamos el ataque
		attacking = true;

		//Cogemos el tiempo actual mas el tiempo de parar  
		stop = SDLApplication::instance()->getCurrentTime() + stopTime;
	}

	setDirectionTo();
	enemyAttack();
}

void TankBehaviour::setDirectionTo() {

    //Si no esta atacando
	if (!attacking) {
		// Persigue al jugador
		pos->lookAt(playerPos->getPos());
	}
	// Se para
	else if (attacking && !chargingAttack) {
		pos->setVel(VECTOR_ZERO);
		if (stop <= SDLApplication::instance()->getCurrentTime()) {
			// Se lanza al jugador en su direccion en linea recta durante X segundos  
			pos->setVel(Vector2D(0, PLAYER_SPEED * 1.5f));
			// Coge la direccion del jugador antes de lanzarse
			pos->lookAt(playerPos->getPos());
			chargingAttack = true;
			attackingTime = SDLApplication::instance()->getCurrentTime() + TANK_ATTACK_TIME;
		}
	}
	else if (attacking && chargingAttack && attackingTime <= SDLApplication::instance()->getCurrentTime()) {
		attacking = false;
		chargingAttack = false;
		pos->setVel(Vector2D(0, TANK_SPEED));
	}
}

void TankBehaviour::enemyAttack() {
	elapsedTime = SDLApplication::instance()->getCurrentTime();

	if (!attacked) {
		//Daña al jugador e informa de que ha atacado
		gObj->getComponent<ColliderComponent>()->hasCollided();
	}
	//Si ha pasado suficiente tiempo para atacar
	else if (elapsedTime >= attackInterval)
	{
		attacked = false;

		//Reseteamos el contador
		behaviorTime -= attackInterval;
	}
}
CallBackCol TankBehaviour::tankAttack()
{
	return [&](GameObject* player) {
		player->getComponent<HealthComponent>()->receiveDamage(damage);
		attacked = true;
		attackInterval = SDLApplication::instance()->getCurrentTime() + MELEE_ENEMY_COOLDOWN;
	};
}