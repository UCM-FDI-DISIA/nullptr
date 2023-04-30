#include "TankBehaviour.h"
#include "../../gameObjects/Card Objects/Hitbox.h"

// Constructora
TankBehaviour::TankBehaviour(float spd, int dmg, float stop, float attack, Player* plyr) : EnemyBehaviour(spd, dmg, stop, attack, plyr), transform(nullptr), startAttack(false), attacked(false), chargingAttack(false), attackingTime(TANK_ATTACK_TIME) {}

void TankBehaviour::initComponent() {

	pos = gObj->getComponent<Transform>();
	// Establece la velocidad
	pos->setVel(Vector2D(0, speed));
	
	// Rota hacia la direccion del jugador
	pos->lookAt(playerPos->getPos());

	elapsedTime = 0;

	gObj->getComponent<ColliderComponent>()->addFunction(tankAttack());
	attackInterval = MELEE_ENEMY_COOLDOWN;
}

void TankBehaviour::update() {
	
	elapsedTime += SDLApplication::instance()->getDeltaTime();
	
	// Si llega a estar a X distancia del jugador y no esta atacando...
	if (!confused && !attacking && pos->getDistance(playerPos->getPos()) <= TANK_ATTACK_DISTANCE && !startAttack ) {
		//Empezamos el ataque
		startAttack = true;
		elapsedTime = 0;
	}

	setDirectionTo();
	enemyAttack();
}


//Funcion para saber la direccion en la que se tiene que mover
void TankBehaviour::setDirectionTo() {
	if (confused) {
		pos->setVel(Vector2D(rand(),rand()).normalize() * TANK_SPEED);
	}
    //Si no esta atacando
	if (!startAttack) {
		// Persigue al jugador
		pos->lookAt(playerPos->getPos());
	}
	// Se para
	else if (startAttack && !chargingAttack) {
		pos->setVel(VECTOR_ZERO);
		if (stopTime <= elapsedTime) {
			// Se lanza al jugador en su direccion en linea recta durante X segundos  
			pos->setVel(Vector2D(0, PLAYER_SPEED * 1.5f));
			// Coge la direccion del jugador antes de lanzarse
			pos->lookAt(playerPos->getPos());
			chargingAttack = true;
			attacking = true;
			elapsedTime = 0;
		}
	}
	else if (attacking && chargingAttack && attackingTime <= elapsedTime) {
		attacking = false;
		startAttack = false;
		chargingAttack = false;
		pos->setVel(Vector2D(0, TANK_SPEED));
	}
}

void TankBehaviour::enemyAttack() {
	

	if (!attacked) {
		//Da�a al jugador e informa de que ha atacado
		attacked = true;
		
	}
	//Si ha pasado suficiente tiempo para atacar
	else if (elapsedTime >= attackInterval && !attacking) 
	{
		attacked = false;

		//Reseteamos el contador
		elapsedTime = 0;
	}
	//Vector2D vel = playerPos->getPos() - pos->getPos();
	//if (vel.magnitude() != 0) {
	//	vel = vel / vel.magnitude();
	//	Vector2D attackPos = pos->getPos() + vel * 100;
	//	float rotation = Vector2D(1, 0).angle(vel);
	//	Hitbox::HitboxData data = { attackPos, VECTOR_ZERO, rotation, 200, 100, "null", _grp_PLAYER };
	//	gStt->addGameObject<Hitbox>(_grp_ENM_ATTACK, damage, true, false, 10, data);
	//	//player->getComponent<HealthComponent>()->receiveDamage(0);
	//}
}

CallBackCol TankBehaviour::tankAttack()
{
	return [&](GameObject* player) {
		player->getComponent<HealthComponent>()->receiveDamage(damage, nullptr, gObj->getComponent<Transform>()->getPos());
		attacked = true;
		attackInterval = SDLApplication::instance()->getCurrentTime() + MELEE_ENEMY_COOLDOWN;
	};
}