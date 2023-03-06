#include "Cards.h"
#include "../../sdlutils/Texture.h"
#include "../Card Objects/Bullet.h"

//Se crea una bala en la posici�n del jugador y se dirige hacia el cursor
void GunCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());
	
	dir = dir.normalize();
	where->addGameObject<Bullet>(_grp_PLYR_ATTACK, playerPos, dir, damage* attackMult, _grp_ENEMIES);
}

//Se disparan todas las balas no usadas con una precisi�n de entre [-90,90] grados
void GunCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	for (int i = 0; i < remainingUses; i++) {
		Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset() - Vector2D(rand() % 90,rand() % 90));

		dir = dir.normalize();

		where->addGameObject<Bullet>(_grp_PLYR_ATTACK, playerPos, dir, damage * attackMult, _grp_ENEMIES);
	}
}
