#include "Cards.h"
#include "../sdlutils/Texture.h"
#include "../gameObjects/SwordSlash.h"
#include "../gameObjects/SwordSpin.h"

#include <iostream>

//SwordCard::SwordCard() {
//	damage = 20;
//	maxUses = 5;
//	remainingUses = maxUses;
//	mana = 80;
//	downtime = 2;
//	name = "Espada";
//	abilityText = "";
//	attackText = "";
//	texture = nullptr;
//}

void SwordCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	std::cout << "slash"<<std::endl;
	
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());

	dir = dir.normalize() * bulletSpeed;
	

	where->addGameObject<SwordSlash>(playerPos, dir, where, damage);

}

void SwordCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	
	where->addGameObject<SwordSpin>(playerPos, where, damage * remainingUses);

}
