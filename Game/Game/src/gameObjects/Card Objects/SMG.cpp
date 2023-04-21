#include "Cards.h"
#include "../../sdlutils/Texture.h"
#include "../../components/Card Components/CardComponent.h"
#include "../Card Objects/Hitbox.h"

//Se crea una bala en la posici�n del jugador y se dirige hacia el cursor
void SMGCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	//Comprobaci�n de que la cadencia no ha sido modificada previamente
	if (downtime != Constant::getFloat("SMG_CADENCE")) downtime = Constant::getFloat("SMG_CADENCE");

	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());

	dir = dir.normalize();

	Hitbox::HitboxData data = { playerPos, dir * Constant::getFloat("BULLET_SPEED"), 0, 30, 30, Constant::getString("BULLET"), _grp_ENEMIES};

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, true, false, 10, data);
}

//Se disparan todas las balas
void SMGCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	//Comprobaci�n de que la cadencia no ha sido modificada previamente
	if (downtime != Constant::getFloat("SMG_CADENCE")) downtime = Constant::getFloat("SMG_CADENCE");
	//Divide el cooldown a la mitad
	downtime /= 2;
	CardComponent* component = where->getPlayer()->getComponent<CardComponent>();
	component->setLocked(true);
	component->setAutomatic(true);
}