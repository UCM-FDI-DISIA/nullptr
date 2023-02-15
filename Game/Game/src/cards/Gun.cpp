#include "Cards.h"
#include "../sdlutils/Texture.h"

Gun::Gun() {
	damage = 10;
	maxUses = 6;
	remainingUses = maxUses;
	mana = 35;
	downtime = 0.5;
	name = "Pistola";
	abilityText = "Se disparan todas las balas como escopeta";
	attackText = "";
	texture = nullptr;
}

void Gun::attack(Vector2D playerPos, Vector2D mousePos, float attackMult) {

}

void Gun::ability(Vector2D playerPos, Vector2D mousePos, float attackMult) {

}
