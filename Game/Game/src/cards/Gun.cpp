#include "Cards.h"
#include "../sdlutils/Texture.h"

Gun::Gun() {
	damage = 20;
	maxUses = 5;
	remainingUses = maxUses;
	mana = 80;
	downtime = 2;
	name = "Pistola";
	abilityText = "";
	attackText = "";
	texture = nullptr;
}

void Gun::attack(Vector2D playerPos, Vector2D mousePos, float attackMult) {

}

void Gun::ability(Vector2D playerPos, Vector2D mousePos, float attackMult) {

}
