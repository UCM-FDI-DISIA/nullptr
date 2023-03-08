#include "Cards.h"
#include "../../sdlutils/Texture.h"
#include "../../components/Card Components/CardComponent.h"
#include "../Card Objects/Bullet.h"

//Se crea una bala en la posición del jugador y se dirige hacia el cursor
void Bow::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	//Comprobación de que la cadencia no ha sido modificada previamente
	if (downtime != SMG_CADENCE) downtime = SMG_CADENCE;

	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());

	dir = dir.normalize();

	where->addGameObject<Bullet>(playerPos, dir, damage * attackMult, where->getEnemies());
}

//Se disparan todas las flechas
void Bow::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {

	for (int i = 0; i < remainingUses; i++) {
		Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset() - Vector2D(rand() % 90, rand() % 90));

		dir = dir.normalize();

		where->addGameObject<Bullet>(playerPos, dir, 5 * remainingUses * attackMult, where->getEnemies());
	}
	remainingUses = 0;

}