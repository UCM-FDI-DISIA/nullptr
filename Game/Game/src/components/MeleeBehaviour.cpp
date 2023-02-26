#include "MeleeBehaviour.h"

MeleeBehaviour::MeleeBehaviour(float stopT, float spd, int dmg, float atkDist, float attack, Player* player) :EnemyBehavior(spd, dmg, stopT, attack, player) {
	attackDistance = atkDist;
}

//Inicializacion de variables necesarias para el componente
void MeleeBehaviour::initComponent() {
	pos = gObj->getComponent<Transform>();
	pos->setVel(Vector2D(0, speed));
	initialDir = pos->getVel();
	pos->lookAt(playerPos->getPos());
	hasBeenCloseToPlayer = false;
	attacked = false;
	elapsedTime = SDL_GetTicks();
}

//Metodo para saber si el enemigo esta cerca del player
bool MeleeBehaviour::close() {

	//Si esta cerca del player
	if (pos->getDistance(playerPos->getPos()) < attackDistance) {
		//Si ya ha estado cerca del player
		if (!hasBeenCloseToPlayer) {
			//Setea elapsed time, velocidad a 0 y marca que ha estado cerca del player ya
			elapsedTime = SDL_GetTicks();
			pos->setVel(Vector2D(0, 0));
			hasBeenCloseToPlayer = true;
		}

		return true; 
	}
	return false;
}

void MeleeBehaviour::update() {
	actualTime = SDL_GetTicks();

	//Si ha estado cerca
	if (close()) {
		//Si no ha atacado y colisiona
		if (!attacked && gObj->getComponent<ColliderComponent>()->hasCollided(player->getComponent<Transform>())) {
			//Daña al jugador e informa de que ha atacado
			player->getComponent<HealthComponent>()->receiveDamage(damage);
			cout << "jaja funciona ";
			Attack();
			attacked = true;
		}
		//Si ha pasado suficiente tiempo para atacar
		if (actualTime - elapsedTime > attackInterval)
		{
			attacked = false;
			

			//Reseteamos el contador
			elapsedTime = SDL_GetTicks();
		}
	}
	else if (hasBeenCloseToPlayer) {
		// Si ha pasado mas tiempo desde que estas parado del que deberia, te mueves
		if (actualTime - elapsedTime > stopTime) {
			pos->setVel(initialDir);
			hasBeenCloseToPlayer = false;
		}
	}
	
	pos->lookAt(playerPos->getPos());
}

// Permite al enemigo instanciar balas
void MeleeBehaviour::Attack() {

	/*Vector2D vel = playerPos->getPos() - pos->getPos();
	if (vel.magnitude() != 0) {
		vel = vel / vel.magnitude();
		
		if (shotPattern == 0) gStt->addGameObject<Bullet>(pos->getPos(), vel / 500, damage, player); // El vel/500 es temporal para que funcione 
		// Hasta que hagamos un deltaTime
		else if (shotPattern == 1) {
			vel = vel.rotate(BULLET_ANGLE);
			gStt->addGameObject<Bullet>(pos->getPos(), vel / 500, damage, player);
			vel = vel.rotate(-2 * BULLET_ANGLE);
			gStt->addGameObject<Bullet>(pos->getPos(), vel / 500, damage, player);
		}
		else if (shotPattern == 2) {
			gStt->addGameObject<Bullet>(pos->getPos(), vel / 500, damage, player);
			vel = vel.rotate(BULLET_ANGLE);
			gStt->addGameObject<Bullet>(pos->getPos(), vel / 500, damage, player);
			vel = vel.rotate(-2 * BULLET_ANGLE);
			gStt->addGameObject<Bullet>(pos->getPos(), vel / 500, damage, player);
		}
	}*/
}

