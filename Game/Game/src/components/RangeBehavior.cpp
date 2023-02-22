#include "RangeBehavior.h"

// Esta clase maneja el comportamiento de los enemigos a distancia
// Como su movimento y su habilidad para atacar
RangeBehavior::RangeBehavior(float spd, float safDist, float stptime, float mvTime, 
	int dmg, int atck, Player* plyr)
	:EnemyBehavior(spd, dmg, stptime, atck, plyr)
{
    safeDistance = safDist;
	moveTime = moveTime;
	shotPattern = rand() % 3;
}
void RangeBehavior::initComponent() {
	pos = gObj->getComponent<Transform>();
	pos->setVel(Vector2D(0.0005, 0.0005)); // El 0.0005 es temporal hasta que hagamos la velocidad bien
	                                       // Es un valor adecuado para que el movimiento funcione
	initialDirection = pos->getVel();
	setDirectionTo();
}
// Se encarga de comprobar si el enemigo est� dentro o fuera del radio de peligro
// Dependiendo de eso, se dirije al jugador o se aleja de �l
void RangeBehavior::setDirectionTo() {
	
	//Si no, vuelve a ir hacia �l
    pos->lookAt(playerPos->getPos());
	//Si estas dentro del rango de peligro, da media vuelta para salir de �l
	if (pos->getDistance(playerPos->getPos()) < safeDistance) pos->rotate(180);
}
// Se trata de un ciclo de movimiento y parada
void RangeBehavior::update() {
	actualTime = SDL_GetTicks();

	// Si ha pasado mas tiempo desde que estas parado del que deberia, te mueves
	if (actualTime - elapsedTime > stopTime)
	{
		pos->setVel(initialDirection);
		// Si te has estado moviendo m�s tiempo de lo que deberia, vuelves al ciclo de parada
		 if (actualTime - elapsedTime > stopTime + moveTime)
		{
			setDirectionTo();
			//pos->setVel(Vector2D(0, 0));
			enemyAttack();
			elapsedTime = actualTime;
		}
	}
}

// Permite al enemigo instanciar balas
void RangeBehavior::enemyAttack() {
	Vector2D vel = playerPos->getPos() - pos->getPos();
	if (vel.magnitude() != 0) {
		vel = vel / vel.magnitude();
		/*vel = vel * bulletSpedd;*/
		if(shotPattern==0) gStt->addGameObject<Bullet>(pos->getPos(), vel / 500, damage, player); // El vel/500 es temporal para que funcione 
		// Hasta que hagamos un deltaTime
		else if (shotPattern == 1) {
			vel = vel.rotate(20);
			gStt->addGameObject<Bullet>(pos->getPos(), vel / 500, damage, player);
			vel = vel.rotate(-40);
			gStt->addGameObject<Bullet>(pos->getPos(), vel / 500, damage, player);
		}
		else if (shotPattern == 2) {
			gStt->addGameObject<Bullet>(pos->getPos(), vel / 500, damage, player);
			vel = vel.rotate(20);
			gStt->addGameObject<Bullet>(pos->getPos(), vel / 500, damage, player);
			vel = vel.rotate(-40);
			gStt->addGameObject<Bullet>(pos->getPos(), vel / 500, damage, player);
		}
	}
}