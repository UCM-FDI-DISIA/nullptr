#include "RangeBehavior.h"

RangeBehavior::RangeBehavior(float spd, float safedist, float stoptime, float movetime, int dmg, float attack)
	:EnemyBehavior(spd, dmg, stoptime, attack)
{
    safeDistance = safedist;
	initialDir = pos->getVel();
	moveTime = movetime;
}
void RangeBehavior::initComponent() {
	setDirectionTo();
}
// Se encarga de comprobar si el enemigo est� dentro o fuera del radio de peligro
// Dependiendo de eso, se dirije al jugador o se aleja de �l
void RangeBehavior::setDirectionTo() {
	//Si estas dentro del rango de peligro, da media vuelta para salir de �l
	if (pos->getDistance(playerPos->getPos()) < safeDistance) pos->rotate(180);
	//Si no, vuelve a ir hacia �l
	else pos->lookAt(playerPos->getPos());
}
// Se trata de un ciclo de movimiento y parada
void RangeBehavior::update() {
	actualTime = SDL_GetTicks();

	// Si ha pasado mas tiempo desde que estas parado del que deberia, te mueves
	if (actualTime - elapsedTime > stopTime)
	{
		// Te mueves Transform.setVel(1)

		// Si te has estado moviendo m�s tiempo de lo que deberia, vuelves al ciclo de parada
		 if (actualTime - elapsedTime > stopTime + moveTime)
		{
			setDirectionTo();
			elapsedTime = SDL_GetTicks();
		}
	}
}
void attack() {
	// Instancia clase bala
}