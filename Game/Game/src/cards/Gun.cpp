#include "Cards.h"
#include "../sdlutils/Texture.h"
#include "../gameObjects/Bullet.h"

GunCard::GunCard() {
	damage = 10;
	maxUses = 6;
	remainingUses = maxUses;
	mana = 35;
	downtime = 0.5;
	bulletSpeed = 0.01f;
	name = "Pistola";
	abilityText = "Se disparan todas las balas como escopeta";
	attackText = "";
	texture = nullptr;
}

void GunCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Vector2D dir = (mousePos-playerPos-where->getCamera()->getOffset());
	
	dir = dir.normalize() * bulletSpeed;

	where->addGameObject(new Bullet(playerPos,dir , where->getCamera(), damage, where->getEnemies(), where->getGame()));
}

void GunCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	for (int i = 0; i < remainingUses; i++) {
		Vector2D dir = (mousePos - playerPos- where->getCamera()->getOffset()- Vector2D(rand()%90,rand() % 90));

		dir = dir.normalize() * bulletSpeed;

		where->addGameObject(new Bullet(playerPos, dir, where->getCamera(), damage, where->getEnemies(), where->getGame()));
	}

}
