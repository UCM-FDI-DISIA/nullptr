#include "Cards.h"
#include "../../sdlutils/Texture.h"
#include "../../components/Card Components/CardComponent.h"
#include "../Card Objects/Bullet.h"

//Se crea una bala en la posición del jugador y se dirige hacia el cursor
void SMGCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	//Comprobación de que la cadencia no ha sido modificada previamente
	if (downtime != SMG_CADENCE) downtime = SMG_CADENCE;

	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());

	dir = dir.normalize();

	where->addGameObject<Bullet>(playerPos, dir, damage * attackMult, _grp_ENEMIES);
}

//Se disparan todas las balas
void SMGCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	//Comprobación de que la cadencia no ha sido modificada previamente
	if (downtime != SMG_CADENCE) downtime = SMG_CADENCE;
	//Divide el cooldown a la mitad
	downtime /= 2;
	CardComponent* component = where->getPlayer()->getComponent<CardComponent>();
	component->setLocked(true);
	component->setAutomatic(true);
}