#include "Cards.h"
#include "../../sdlutils/Texture.h"
#include "../../components/Card Components/CardComponent.h"
#include "../Card Objects/Bullet.h"
#include "DamageArea.h"

//Se crea una bala en la posición del jugador y se dirige hacia el cursor
void Bow::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	//Comprobación de que la cadencia no ha sido modificada previamente
	if (downtime != BOW_CADENCE) downtime = BOW_CADENCE;

	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());

	dir = dir.normalize();

	where->addGameObject<Bullet>(playerPos, dir, damage * attackMult, where->getEnemies());
}

//Se disparan todas las flechas
void Bow::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {

		Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset() - Vector2D(rand() % 90, rand() % 90));
		dir = dir.normalize();
		where->addGameObject<DamageArea>(mousePos, where, damage * attackMult, int(remainingUses / 2));


	remainingUses = 0;

}