#include "TankBehaviour.h"

// Constructora
TankBehaviour::TankBehaviour(float spd, int dmg, float stop, float attack, Player* plyr) : EnemyBehaviour(spd, dmg, stop, attack, plyr), transform(nullptr), startAttack(false), attacked(false), chargingAttack(false),  stop(stopTime), attackingTime(Constant::getFloat("TANK_ATTACK_TIME")) {}

void TankBehaviour::initComponent() {

	pos = gObj->getComponent<Transform>();
	// Establece la velocidad
	pos->setVel(Vector2D(0, speed));
	
	// Rota hacia la direccion del jugador
	pos->lookAt(playerPos->getPos());

	elapsedTime = 0;

	gObj->getComponent<ColliderComponent>()->addFunction(tankAttack());
}

void TankBehaviour::update() {
	
	elapsedTime += SDLApplication::instance()->getDeltaTime();
	
	// Si llega a estar a X distancia del jugador y no esta atacando...
	if (!confused && !attacking&& pos->getDistance(playerPos->getPos()) <= Constant::getFloat("TANK_ATTACK_DISTANCE")) {
		//Empezamos el ataque
		startAttack = true;

		//Cogemos el tiempo actual mas el tiempo de parar  
		stop = elapsedTime + stopTime;
	}

	setDirectionTo();
	enemyAttack();
}

void TankBehaviour::setDirectionTo() {
	if (confused) {
		pos->setVel(Vector2D(rand(),rand()).normalize() * Constant::getFloat("TANK_SPEED"));
	}
    //Si no esta atacando
	if (!startAttack) {
		// Persigue al jugador
		pos->lookAt(playerPos->getPos());
	}
	// Se para
	else if (startAttack && !chargingAttack) {
		pos->setVel(Vector2D());
		if (stop <= elapsedTime) {
			// Se lanza al jugador en su direccion en linea recta durante X segundos  
			pos->setVel(Vector2D(0, Constant::getFloat("PLAYER_SPEED") * 1.5f));
			// Coge la direccion del jugador antes de lanzarse
			pos->lookAt(playerPos->getPos());
			chargingAttack = true;
			attacking = true;
			attackingTime = elapsedTime + Constant::getFloat("TANK_ATTACK_TIME");
		}
	}
	else if (attacking && chargingAttack && attackingTime <= elapsedTime) {
		attacking = false;
		startAttack = false;
		chargingAttack = false;
		pos->setVel(Vector2D(0, Constant::getFloat("TANK_SPEED")));
	}
}

void TankBehaviour::enemyAttack() {
	

	if (!attacked) {
		//Da�a al jugador e informa de que ha atacado
		attacked = true;
		attackInterval = elapsedTime + Constant::getFloat("MELEE_ENEMY_COOLDOWN");
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
		attackInterval = SDLApplication::instance()->getCurrentTime() + Constant::getFloat("MELEE_ENEMY_COOLDOWN");
	};
}