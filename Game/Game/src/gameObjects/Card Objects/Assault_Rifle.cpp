#include "Cards.h"
#include "../../sdlutils/Texture.h"
#include "../../components/Card Components/CardComponent.h"
#include "../Card Objects/Bullet.h"
#include "Bomb.h"

//Se crea una bala en la posición del jugador y se dirige hacia el cursor
void Assault_Rifle::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	for (int i = 0; i < 4 ; i++) {
		Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());

		dir = dir.normalize();

		playerPos = playerPos - dir * ASSAULT_RIFLE_BURST;
		where->addGameObject<Bullet>(_grp_PLYR_ATTACK, playerPos, dir, damage * attackMult, _grp_ENEMIES);
	}
}

//Se disparan todas las balas
void Assault_Rifle::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());

	dir = dir.normalize();
	where->addGameObject<Bomb>(_grp_PLYR_ATTACK, playerPos, dir, 50 * (remainingUses / 8), where, _grp_ENEMIES);

}