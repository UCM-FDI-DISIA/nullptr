#include "Cards.h"
#include "../sdlutils/Texture.h"
#include <iostream>

SwordCard::SwordCard() {
	damage = 20;
	maxUses = 5;
	remainingUses = maxUses;
	mana = 80;
	downtime = 2;
	name = "Espada";
	abilityText = "";
	attackText = "";
	texture = nullptr;
}

void SwordCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult) {
	std::cout << "slash"<<std::endl;
}

void SwordCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult) {

}
