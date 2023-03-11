#include "Cards.h"
#include "../../sdlutils/Texture.h"
#include "../Card Objects/Hitbox.h"

//Se crea una bala en la posición del jugador y se dirige hacia el cursor
void Assault_Rifle::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	for (int i = 0; i < 4 ; i++) {
		Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());

		dir = dir.normalize();

		playerPos = playerPos - dir * ASSAULT_RIFLE_BURST;
		Hitbox::HitboxData data = { playerPos, dir * BULLET_SPEED, 0, 30, 30, "Bullet", _grp_ENEMIES };

		where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, true, false, 10, data);
	}
}

//Se disparan todas las balas
void Assault_Rifle::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());

	dir = dir.normalize();

	Hitbox::HitboxData data = { playerPos, dir * BULLET_SPEED, 0, 16, 16, "Bullet", _grp_ENEMIES };

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, 50 * (remainingUses / 8), true, 3, where, data);

	remainingUses = 0;

}