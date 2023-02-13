#include "laserShades.h"
#include "../sdlutils/Texture.h"

LaserShades::LaserShades() {
	damage = 20;
	maxUses = 5;
	remainingUses = maxUses;
	mana = 80;
	downtime = 2;
	name = "Gafas Láser";
	abilityText = "";
	attackText = "";
	texture = nullptr;
}

void LaserShades::attack(Vector2D playerPos, Vector2D mousePos, float attackMult) {

}

void LaserShades::ability(Vector2D playerPos, Vector2D mousePos, float attackMult) {

}
