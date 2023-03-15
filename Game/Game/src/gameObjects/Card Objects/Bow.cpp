#include "Cards.h"
#include "../../sdlutils/Texture.h"
#include "../../components/Card Components/CardComponent.h"
#include "Hitbox.h"

//Se crea una bala en la posición del jugador y se dirige hacia el cursor
void BowCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	//Comprobación de que la cadencia no ha sido modificada previamente
	if (downtime != BOW_CADENCE) downtime = BOW_CADENCE;

	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());

	dir = dir.normalize();

	Hitbox::HitboxData data = { playerPos, dir * ARROW_SPEED, 0, 30, 30, "Bullet", _grp_ENEMIES };

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, true, false, 10, data);
}

//Se disparan todas las flechas
void BowCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {

		Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());
		dir = dir.normalize();

		Hitbox::HitboxData data = { playerPos, dir * ARROW_SPEED, 0, 16, 16, "Bullet", _grp_ENEMIES };
		float size = 100 + remainingUses * 15;
		string sprite = "Bullet";

		where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, 2, HitboxStatusComponent::NONE, size, size, sprite, where, data);


	remainingUses = 0;

}