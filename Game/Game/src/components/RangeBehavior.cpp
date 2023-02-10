#include "RangeBehavior.h"
RangeBehavior::RangeBehavior(Manager* mgr, GameObject* gmObj,Transform* Pos ,Transform* playerpos, float spd, float safedist, float stoptime, float movetime)
	:EnemyBehavior(mgr, gmObj,Pos, playerPos,spd)
{
	safeDistance = safedist;
	initialDir = Pos->getVel();
	stopTime = stoptime;
	moveTime = movetime;
}
void RangeBehavior::setDirectionTo()
{
	//Si estas dentro del rango de peligro, da media vuelta para salir de él
	if (pos->getDistance(playerPos->getPos()) < safeDistance) pos->rotate(180);
	//Si no, vuelve a ir hacia él
	else pos->lookAt(playerPos->getPos());
}
// Se trata de un ciclo de movimiento y parada
void RangeBehavior::update()
{
	actualTime = SDL_GetTicks();
	setDirectionTo();
	// Si ha pasado mas tiempo desde que estas parado del que deberia, te mueves
	if (actualTime - elapsedTime > stopTime)
	{
		// Te mueves Movecomponent.Move()

		// Si te has estado moviendo más tiempo de lo que deberia, vuelves al ciclo de parada
		if (actualTime - elapsedTime > stopTime + moveTime)
		{
			elapsedTime = SDL_GetTicks();
		}
	}
}