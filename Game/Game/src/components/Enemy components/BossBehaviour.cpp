#include "BossBehaviour.h"

// Esta clase maneja el comportamiento de los enemigos a distancia
// Como su movimento y su habilidad para atacar
BossBehaviour::BossBehaviour(float spd, float safDist, float stptime, float mvTime,
	int dmg, int atck, Player* plyr) :
	EnemyBehaviour(spd, dmg, stptime, atck, plyr),
	safeDistance(safDist), moveTime(mvTime), shotPattern(sdlutils().rand().nextInt(0, 3)),
	attackDelay(RANGED_ATTACK_ANIM_DELAY), attackTime(0) {}


void BossBehaviour::initComponent() {
	pos = gObj->getComponent<Transform>();
	pos->setVel(Vector2D(0, 0)); 
	setDirectionTo();
}
// Se encarga de comprobar si el enemigo este dentro o fuera del radio de peligro
// Dependiendo de eso, se dirije al jugador o se aleja de el
void BossBehaviour::setDirectionTo() {
	if (confused) {
		pos->setVel(Vector2D(rand(), rand()).normalize() * speed);
	}
	else {
		//Si no, vuelve a ir hacia el
		pos->lookAt(playerPos->getPos());
		//Si estas dentro del rango de peligro, da media vuelta para salir de el
		if (pos->getDistance(playerPos->getPos()) < safeDistance) pos->rotate(180);
	}
}
// Se trata de un ciclo de movimiento y parada
void BossBehaviour::update() {
	behaviorTime += SDLApplication::instance()->getDeltaTime();

	// Si ha pasado mas tiempo desde que estas parado del que deberia, te mueves
	if (behaviorTime > stopTime)
	{
		pos->setVel(initialDirection);

		// Si te has estado moviendo mas tiempo de lo que deberia, vuelves al ciclo de parada
		if (behaviorTime > stopTime + moveTime) {
			setDirectionTo();
			//pos->setVel(Vector2D(0, 0));
			attacking = true; // comienza la animación de ataque
			behaviorTime -= stopTime + moveTime;
		}
	}
	if (!confused) {
		if (attacking) {
			if (attackDelay < attackTime) {
				attackTime = 0;
				attacking = false;
				//enemyAttack(); // ataca coincidiendo con la animación  attackState
				switch (3) {
				case 0: // Conos
					coneAttack();
					break;
				case 1: // BulletHell
					bulletHellAttack();
					break;
				case 2: // Conos
					coneAttack();
					break;
				case 3: // Granadas
					grenadeAttack();
					break;
				case 4: // Tentáculo Dirigido
					tentacleDirectedAttack();
					break;
				case 5: // Aspersor
					sprinklerAttack();
					break;
				case 6: // BulletHell + Granadas
					bulletHellAttack();
					grenadeAttack();
					break;
				case 7: // Tentáculo Dirigido + Conos
					tentacleDirectedAttack();
					coneAttack();
					break;
				case 8: // BulletHell + Aspersor
					bulletHellAttack();
					sprinklerAttack();
					break;
				case 9: // Granadas + Tentáculo Dirigido
					grenadeAttack();
					tentacleDirectedAttack();
					break;
				default:
					break;
				}
			}
			else attackTime += SDLApplication::instance()->getDeltaTime();
		}
	}
}

// Permite al enemigo instanciar balas
void BossBehaviour::enemyAttack() {
	Vector2D vel = playerPos->getPos() - pos->getPos();
	if (vel.magnitude() != 0) {
		vel = vel / vel.magnitude();
		Hitbox::HitboxData data = { pos->getPos(), vel * BULLET_SPEED, 0, 30, 30, "Bullet", _grp_PLAYER };
		/*vel = vel * bulletSpedd;*/
		if (shotPattern == 0) {
			gStt->addGameObject<Hitbox>(_grp_ENM_ATTACK, damage, true, false, 10, data);
		}
		else if (shotPattern == 1) {
			vel = vel.rotate(BULLET_ANGLE);
			data = { pos->getPos(), vel * BULLET_SPEED, 0, 30, 30, "Bullet", _grp_PLAYER };
			gStt->addGameObject<Hitbox>(_grp_ENM_ATTACK, damage, true, false, 10, data);
			vel = vel.rotate(-2 * BULLET_ANGLE);
			data = { pos->getPos(), vel * BULLET_SPEED, 0, 30, 30, "Bullet", _grp_PLAYER };
			gStt->addGameObject<Hitbox>(_grp_ENM_ATTACK, damage, true, false, 10, data);
		}
		else if (shotPattern == 2) {	
			gStt->addGameObject<Hitbox>(_grp_ENM_ATTACK, damage, true, false, 10, data);
			vel = vel.rotate(BULLET_ANGLE);
			data = { pos->getPos(), vel * BULLET_SPEED, 0, 30, 30, "Bullet", _grp_PLAYER };
			gStt->addGameObject<Hitbox>(_grp_ENM_ATTACK, damage, true, false, 10, data);
			vel = vel.rotate(-2 * BULLET_ANGLE);
			data = { pos->getPos(), vel * BULLET_SPEED, 0, 30, 30, "Bullet", _grp_PLAYER };
			gStt->addGameObject<Hitbox>(_grp_ENM_ATTACK, damage, true, false, 10, data);
		}
	}
}
// Función para ejecutar el ataque de Conos
void BossBehaviour::coneAttack() {
	// Implementar lógica del ataque de Conos
}

// Función para ejecutar el ataque Bullet Hell
void BossBehaviour::bulletHellAttack() {
	// Definimos la cantidad de balas y la separación entre ellas
	const int numBullets = 10;
	const float bulletSeparation = 20.0f;
	// Obtenemos la dirección hacia el jugador
	Vector2D dir = (playerPos->getPos() - pos->getPos()).normalize();

	// Calculamos la posición inicial para las balas
	Vector2D startPos = pos->getPos() + dir * 50.0f;

	// Generamos las balas
	for (int i = 0; i < numBullets; i++) {
		// Calculamos la dirección de la bala
		float angle = (float)i * (360.0f / (float)numBullets);
		Vector2D bulletDir = dir.rotate(angle);

		// Calculamos la posición de la bala
		Vector2D bulletPos = startPos + bulletDir * bulletSeparation * i;

		// Creamos el objeto de la bala
		Hitbox::HitboxData data = { bulletPos, bulletDir * BULLET_SPEED, 0, 30, 30, "Bullet", _grp_PLAYER };
		gStt->addGameObject<Hitbox>(_grp_ENM_ATTACK, damage, true, false, 10, data);
	}
}

// Función para ejecutar el ataque Tentáculo Dirigido
void BossBehaviour::tentacleDirectedAttack() {
	// Implementar lógica del ataque Tentáculo Dirigido
}

// Función para ejecutar el ataque Aspersor
void BossBehaviour::sprinklerAttack() {
	// Implementar lógica del ataque Aspersor
}

// Función para ejecutar el ataque Granadas
void BossBehaviour::grenadeAttack() {
	// Implementar lógica del ataque Granadas
	Vector2D directions[] = { Vector2D(1,0), Vector2D(0,1), Vector2D(-1,0), Vector2D(0,-1) };

	// Creo la funcion que instancia 8 balas al explotar
	CallBackExpl bossGrenade = [myScene = gStt](Transform* tr) {
		// Direcciones de las balas
		Vector2D directs[] = {Vector2D(1,0), Vector2D(-1,0), Vector2D(0,1), Vector2D(0,-1), 
			Vector2D(1,1).normalize(), Vector2D(1,-1).normalize(), Vector2D(-1,1).normalize(), Vector2D(-1,-1).normalize()};
		// Creo las 8 balas
		for (int i = 0; i < 8; i++) {
			Hitbox::HitboxData data = { tr->getCenter(), directs[i] * BULLET_SPEED, 0, 30, 30, "Bullet", _grp_PLAYER};
			myScene->addGameObject<Hitbox>(_grp_ENM_ATTACK, 20, true, false, 10, data);
		}
	};
	// Creo las 4 granadas en direcciones arriba, abajo, izq y der
	for (int i = 0; i < 4; i++) {
		Hitbox::HitboxData data = {gObj->getComponent<Transform>()->getCenter(), directions[i] * BULLET_SPEED, 0, 50, 50, FLASH_BANG, _grp_PLAYER};
		gStt->addGameObject<Hitbox>(_grp_ENM_ATTACK, 5, true, 1, StatusComponent::NONE, 200, 200, FLASH_BANG, dynamic_cast<BattleScene*>(gStt), data, Vector2D(-1,-1), bossGrenade);
	}
}