#include "Cards.h"
#include "../sdlutils/Texture.h"

Sword::Sword() {
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

void Sword::attack(Vector2D playerPos, Vector2D mousePos, float attackMult) {

}

void Sword::ability(Vector2D playerPos, Vector2D mousePos, float attackMult) {

}
