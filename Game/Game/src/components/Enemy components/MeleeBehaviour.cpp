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
	gObj->getComponent<ColliderComponent>()->addFunction(meleeAttack());
}

//Metodo para saber si el enemigo esta cerca del player
void MeleeBehaviour::close() {

	//Si esta cerca del player
	if (pos->getDistance(playerPos->getPos()) < attackDistance) {
		//Si ya ha estado cerca del player
		if (!hasBeenCloseToPlayer) {
			//Setea elapsed time, velocidad a 0 y marca que ha estado cerca del player ya
			behaviorTime = SDLApplication::instance()->getCurrentTime() + stopTime;
			pos->setVel(Vector2D(0, 0));
			hasBeenCloseToPlayer = true;
		}
	}
}

void MeleeBehaviour::update() {
	elapsedTime += SDLApplication::instance()->getDeltaTime();
	close();
	if (hasBeenCloseToPlayer) {
		// Si ha pasado mas tiempo desde que estas parado del que deberia, te mueves
		if (elapsedTime >= behaviorTime) {
			pos->setVel(initialDir);
			hasBeenCloseToPlayer = false;
		}
	}

	
	//Si ha pasado suficiente tiempo para atacar
	else if (elapsedTime>= attackInterval)
	{
		attacked = false;

		//Reseteamos el contador
		behaviorTime -= attackInterval;
	}
	
	pos->lookAt(playerPos->getPos());
}
// Funci�n a realizar en colision
CallBackCol MeleeBehaviour::meleeAttack()
{
	return [&](GameObject* gameObject)
	{
		//Da�a al jugador e informa de que ha atacado
		player->getComponent<HealthComponent>()->receiveDamage(damage);
		attacked = true;
	};
}



