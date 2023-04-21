#include "Cards.h"
#include "../../sdlutils/Texture.h"
#include "../Card Objects/Hitbox.h"

//Se crea una bala en la posici�n del jugador y se dirige hacia el cursor
void  AssaultRifleCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	for (int i = 0; i < 4 ; i++) {
		Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());

		dir = dir.normalize();

		playerPos = playerPos - dir * Constant::getFloat("ASSAULT_RIFLE_BURST");

		Hitbox::HitboxData data = { playerPos, dir * Constant::getFloat("BULLET_SPEED"), 0, 30, 30, Constant::getString("BULLET"), _grp_ENEMIES};

		where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, true, false, 10, data);
	}
}

void  AssaultRifleCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());
	dir = dir.normalize();

	Hitbox::HitboxData data = { playerPos, dir * Constant::getFloat("BULLET_SPEED"), 0, 16, 16, Constant::getString("BULLET"), _grp_ENEMIES };
	float size = 250;
	string sprite = "Bullet";

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, 50 * (remainingUses / 8), false, 2, StatusComponent::NONE, size, size, sprite, where, data);


	remainingUses = 0;

}