#include "Cards.h"
#include "../sdlutils/Texture.h"
#include "../gameObjects/Bullet.h"


void GunCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());
	
	dir = dir.normalize() * bulletSpeed;

	where->addGameObject<Bullet>(playerPos, dir, damage, where->getEnemies());
}

void GunCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	for (int i = 0; i < remainingUses; i++) {
		Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset() - Vector2D(rand() % 90,rand() % 90));

		dir = dir.normalize() * bulletSpeed;

		where->addGameObject<Bullet>(playerPos, dir, damage, where->getEnemies());
	}
}
