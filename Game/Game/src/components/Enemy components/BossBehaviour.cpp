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
			attacking = true; // comienza la animaci�n de ataque
			behaviorTime -= stopTime + moveTime;
		}
	}
	if (!confused) {
		if (attacking) {
			if (attackDelay < attackTime) {
				attackTime = 0;
				attacking = false;
				//enemyAttack(); // ataca coincidiendo con la animaci�n  attackState
				switch (0) {
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
				case 4: // Tent�culo Dirigido
					tentacleDirectedAttack();
					break;
				case 5: // Aspersor
					sprinklerAttack();
					break;
				case 6: // BulletHell + Granadas
					bulletHellAttack();
					grenadeAttack();
					break;
				case 7: // Tent�culo Dirigido + Conos
					tentacleDirectedAttack();
					coneAttack();
					break;
				case 8: // BulletHell + Aspersor
					bulletHellAttack();
					sprinklerAttack();
					break;
				case 9: // Granadas + Tent�culo Dirigido
					grenadeAttack();
					tentacleDirectedAttack();
					break;
				default:
					break;
				}
				if (attackState == 9 && !listaCompletada)
				{
					listaCompletada = true;
				}
				if (!listaCompletada)
				{
					attackState++;
				}
				else
				{
					attackState = rand() % 10;
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
//// Funci�n para ejecutar el ataque de Conos
//void BossBehaviour::coneAttack() {
//	// Obtener la direcci�n hacia el objetivo (en este caso, el player)
//	Vector2D dir = (playerPos->getPos() - pos->getPos());
//	dir = dir / dir.magnitude();
//
//	// Generar los ataques de cono en direcci�n al jugador y en direcci�n contraria
//	for (int i = 0; i < 2; i++) {
//		Vector2D coneDir = dir.rotate(i * 180);
//		Vector2D hitboxDir;
//
//		if (i % 2 == 0) {
//			hitboxDir = coneDir.rotate(45);
//		}
//		else {
//			hitboxDir = coneDir.rotate(315);
//		}
//
//		Vector2D hitboxPos = pos->getPos() + coneDir * 100;
//		float rotation = Vector2D(1, 0).angle(coneDir);
//		Hitbox::HitboxData data = { hitboxPos, VECTOR_ZERO, rotation, 200, 200, CONE_BOSS, _grp_PLAYER };
//		gStt->addGameObject<Hitbox>(_grp_ENM_ATTACK, damage, true, false, 10, data);
//	}
//
//	// Incrementar el contador de ataques y reiniciar el tiempo de ataque
//	attackTime = 0;
//
//	// Reiniciar behaviorTime para empezar de nuevo
//	behaviorTime = 0;
//}
// Modifica la función coneAttack
void BossBehaviour::coneAttack() {
	// Obtener la dirección hacia el objetivo (en este caso, el player)
	Vector2D dir = (playerPos->getPos() - pos->getPos());
	dir = dir / dir.magnitude();

	// Generar los ataques de cono en dirección al jugador y en dirección contraria
	for (int i = 0; i < 2; i++) {
		Vector2D coneDir = dir.rotate(i * 180 + coneAttacksDone * 90);
		Vector2D hitboxDir;

		if (i % 2 == 0) {
			hitboxDir = coneDir.rotate(45);
		}
		else {
			hitboxDir = coneDir.rotate(315);
		}

		Vector2D hitboxPos = pos->getPos() + coneDir * 100;
		float rotation = Vector2D(1, 0).angle(coneDir);
		Hitbox::HitboxData data = { hitboxPos, VECTOR_ZERO, rotation, 200, 200, CONE_BOSS, _grp_PLAYER };
		gStt->addGameObject<Hitbox>(_grp_ENM_ATTACK, damage, true, false, 10, data);
	}

	// Incrementar el contador de ataques de cono
	coneAttacksDone++;

	// Si aún no se han realizado los 4 ataques de cono, llamar a coneAttack() nuevamente después de 2 segundos
	if (coneAttacksDone < 4) {
		// Utiliza la función SDL_AddTimer para llamar a coneAttack() nuevamente después de 2 segundos (2000 ms)
		SDL_AddTimer(2000, &BossBehaviour::coneAttackTimerCallback, this);
	}
	else {
		// Reiniciar coneAttacksDone
		coneAttacksDone = 0;
	}

	// Incrementar el contador de ataques y reiniciar el tiempo de ataque
	attackTime = 0;

	// Reiniciar behaviorTime para empezar de nuevo
	behaviorTime = 0;
}



// Funci�n para ejecutar el ataque Bullet Hell
void BossBehaviour::bulletHellAttack() {
	// Definimos la cantidad de balas y la separaci�n entre ellas
	const int numBullets = 10;
	const float bulletSeparation = 20.0f;
	// Obtenemos la direcci�n hacia el jugador
	Vector2D dir = (playerPos->getPos() - pos->getPos()).normalize();

	// Calculamos la posici�n inicial para las balas
	Vector2D startPos = pos->getPos() + dir * 50.0f;

	// Generamos las balas
	for (int i = 0; i < numBullets; i++) {
		// Calculamos la direcci�n de la bala
		float angle = (float)i * (360.0f / (float)numBullets);
		Vector2D bulletDir = dir.rotate(angle);

		// Calculamos la posici�n de la bala
		Vector2D bulletPos = startPos + bulletDir * bulletSeparation * i;

		// Creamos el objeto de la bala
		Hitbox::HitboxData data = { bulletPos, bulletDir * BULLET_SPEED, 0, 30, 30, "Bullet", _grp_PLAYER };
		gStt->addGameObject<Hitbox>(_grp_ENM_ATTACK, damage, true, false, 10, data);
	}
}

// Funci�n para ejecutar el ataque Tent�culo Dirigido
void BossBehaviour::tentacleDirectedAttack() {
	// Implementar l�gica del ataque Tent�culo Dirigido
}

// Funci�n para ejecutar el ataque Aspersor
void BossBehaviour::sprinklerAttack() {
	// Implementar l�gica del ataque Aspersor
}
// Funci�n para ejecutar el ataque Granadas
void BossBehaviour::grenadeAttack() {
	// Implementar l�gica del ataque Granadas
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

// Función de devolución de llamada del temporizador para coneAttack
Uint32 BossBehaviour::coneAttackTimerCallback(Uint32 interval, void* param) {
	BossBehaviour* boss = static_cast<BossBehaviour*>(param);
	boss->coneAttack();
	return 0;
}
