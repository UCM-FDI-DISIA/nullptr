#include "MeleeBehaviour.h"
MeleeBehaviour::MeleeBehaviour(float stopT, float spd, int dmg, float atkDist, float attack, Player* player) :EnemyBehavior(spd, dmg, stopT, attack, player) {
	initialDir = pos->getVel();
	attackDistance = atkDist;
}

void MeleeBehaviour::initComponent() {
	
	moveTo();
	closeToPlayer = false;
	elapsedTime = SDL_GetTicks();
}

void MeleeBehaviour::moveTo() {
	pos->lookAt(playerPos->getPos());
}

bool MeleeBehaviour::close() {

	//Si esta cerca del player
	if (pos->getDistance(playerPos->getPos()) <= attackDistance) {
		//Si ya ha estado cerca del player
		if (!closeToPlayer) {
			//Setea elapsed time, velocidad a 0 y marca que ha estado cerca del player ya
			elapsedTime = SDL_GetTicks();
			pos->setVel(Vector2D(0, 0));
			closeToPlayer = true;
		}

		return true; 
	}
	else return false;
}

void MeleeBehaviour::update() {
	actualTime = SDL_GetTicks();

	if (close()) {
		
		//Si ha pasado suficiente tiempo para atacar
		if (actualTime - elapsedTime > attackInterval)
		{
			//Ataca
			/*attack();*/

			//Reseteamos el contador
			elapsedTime = SDL_GetTicks();
		}
	}
	else if (closeToPlayer) {
		// Si ha pasado mas tiempo desde que estas parado del que deberia, te mueves
		if (actualTime - elapsedTime > stopTime) {
			pos->setVel(initialDir);
		}
		closeToPlayer = false;
	}
	
	moveTo();
}



