#include "Cards.h"
#include "../Card Objects/Hitbox.h"
#include "../../scenes/GameState.h"

//Se crea una bala en la posici�n del jugador y se dirige hacia el cursor
void GunCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());
	
	dir = dir.normalize();
	float rot = where->getPointer()->getComponent<Transform>()->getRotation() - 90;
	Hitbox::HitboxData data = { playerPos, dir * GUN_BULLET_SPEED, rot, 20, 10, BULLET, _grp_ENEMIES };

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, true, 10, data);

}

//Se disparan todas las balas no usadas con una precisi�n de entre [-90,90] grados
void GunCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	for (int i = 0; i < remainingUses; i++) {
		Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset() - Vector2D(rand() % 90,rand() % 90));

		dir = dir.normalize();

		float rot = Vector2D(1,0).angle(dir.normalize());
		Hitbox::HitboxData data = { playerPos, dir * GUN_BULLET_SPEED, rot, 20, 10, BULLET, _grp_ENEMIES };

		where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, true, 10, data);
	}
	remainingUses = 0;
}
