#include "RangeBehavior.h"
RangeBehavior::RangeBehavior(float spd, float safedist, float stoptime, float movetime)
	:EnemyBehavior(spd) {
	safeDistance = safedist;
	initialDir = pos->getVel();
	stopTime = stoptime;
	moveTime = movetime;
}
void RangeBehavior::initComponent() {
	setDirectionTo();
}
// Se encarga de comprobar si el enemigo está dentro o fuera del radio de peligro
// Dependiendo de eso, se dirije al jugador o se aleja de él
void RangeBehavior::setDirectionTo() {
	//Si estas dentro del rango de peligro, da media vuelta para salir de él
	if (pos->getDistance(playerPos->getPos()) < safeDistance) pos->rotate(180);
	//Si no, vuelve a ir hacia él
	else pos->lookAt(playerPos->getPos());
}
// Se trata de un ciclo de movimiento y parada
void RangeBehavior::update() {
	actualTime = SDL_GetTicks();

	// Si ha pasado mas tiempo desde que estas parado del que deberia, te mueves
	if (actualTime - elapsedTime > stopTime)
	{
		// Te mueves Transform.setVel(1)

		// Si te has estado moviendo más tiempo de lo que deberia, vuelves al ciclo de parada
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