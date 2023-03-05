#include "MeleeBehaviour.h"
#include "../../core/SDLApplication.h"

MeleeBehaviour::MeleeBehaviour(float stopT, float spd, int dmg, float atkDist, float attack, Player* player) :EnemyBehaviour(spd, dmg, stopT, attack, player) {
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
	behaviorTime += SDLApplication::instance()->getDeltaTime();

	//Si ha estado cerca
	if (close()) {
		//Si no ha atacado y colisiona
		if (!attacked) {
			gObj->getComponent<ColliderComponent>()->hasCollided();
		}
		//Si ha pasado suficiente tiempo para atacar
		if (behaviorTime > attackInterval)
		{
			attacked = false;
			

			//Reseteamos el contador
			behaviorTime -= attackInterval;
		}
	}
	else if (hasBeenCloseToPlayer) {
		// Si ha pasado mas tiempo desde que estas parado del que deberia, te mueves
		if (behaviorTime - elapsedTime > stopTime) {
			pos->setVel(initialDir);
			hasBeenCloseToPlayer = false;
		}
	}
	
	pos->lookAt(playerPos->getPos());
}
CallBackCol MeleeBehaviour::meleeAttack()
{
	return [&](GameObject* gameObject)
	{
		//Daña al jugador e informa de que ha atacado
		player->getComponent<HealthComponent>()->receiveDamage(damage);
		attacked = true;
	};
}



