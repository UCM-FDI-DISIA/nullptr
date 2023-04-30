#include "Cards.h"
#include "../../sdlutils/Texture.h"
#include "../Card Objects/Hitbox.h"

//Se crea una bala en la posición del jugador y se dirige hacia el cursor
void  LightRifleCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
		Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());
		dir = dir.normalize();

		Hitbox::HitboxData data = { playerPos, dir * LIGHT_BULLET_SPEED, 0, 30, 30, BULLET, _grp_ENEMIES };
		where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, true, 10, data);
}

//Se disparan todas las balas
void  LightRifleCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());
	dir = dir.normalize();

	Hitbox::HitboxData data = { playerPos, dir * BULLET_SPEED, 0, 16, 16, BULLET, _grp_ENEMIES };

	float size = 100 + 20 * remainingUses;

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, 0, true, 2, StatusComponent::BURNED, size, size, "Bullet", where, data);



	remainingUses = 0;

}