#include "Cards.h"
#include "../../sdlutils/Texture.h"
#include "../Card Objects/Hitbox.h"

//Se crea una bala en la posici�n del jugador y se dirige hacia el cursor
void  LightRifleCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
		Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());
		dir = dir.normalize();

		Hitbox::HitboxData data = { playerPos, dir * Constant::getFloat("LIGHT_BULLET_SPEED"), 0, 30, 30, Constant::getString("BULLET"), _grp_ENEMIES };
		where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, true, false, 10, data);
}

//Se disparan todas las balas
void  LightRifleCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());
	dir = dir.normalize();

	Hitbox::HitboxData data = { playerPos, dir * Constant::getFloat("BULLET_SPEED"), 0, 16, 16, Constant::getString("BULLET"), _grp_ENEMIES };

	float size = 100 + 20 * remainingUses;

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, 0, true, 2, StatusComponent::BURNED, size, size, Constant::getString("BULLET"), where, data);



	remainingUses = 0;

}