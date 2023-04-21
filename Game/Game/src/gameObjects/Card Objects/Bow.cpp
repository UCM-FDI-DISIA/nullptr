#include "Cards.h"
#include "../../sdlutils/Texture.h"
#include "../../components/Card Components/CardComponent.h"
#include "Hitbox.h"

//Se crea una bala en la posici�n del jugador y se dirige hacia el cursor
void BowCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	//Comprobaci�n de que la cadencia no ha sido modificada previamente
	if (downtime != Constant::getFloat("BOW_CADENCE")) downtime = Constant::getFloat("BOW_CADENCE");

	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());

	dir = dir.normalize();

	Hitbox::HitboxData data = { playerPos, dir * Constant::getFloat("ARROW_SPEED"), 0, 30, 30, Constant::getString("BULLET"), _grp_ENEMIES };

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, true, false, 10, data);
}

//Se disparan todas las flechas
void BowCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {

		Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());
		dir = dir.normalize();

		Hitbox::HitboxData data = { playerPos, dir * Constant::getFloat("ARROW_SPEED"), 0, 16, 16, Constant::getString("BULLET"), _grp_ENEMIES };

		float size = 100 + remainingUses * 15;
		where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, 2, StatusComponent::NONE, size, size, Constant::getString("BULLET"), where, data);


	remainingUses = 0;

}