#include "Cards.h"
#include "../../sdlutils/Texture.h"
#include "../Card Objects/SwordSlash.h"
#include "../Card Objects/SwordSpin.h"

#include <iostream>

// Crea un gObj Slash en la dirección que apunta el jugador
void SwordCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();	

	where->addGameObject<SwordSlash>(playerPos, dir, where, damage * attackMult);

}

// Crea un gObj Spin en el centro del jugador
void SwordCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	
	where->addGameObject<SwordSpin>(playerPos, where, damage * remainingUses * attackMult);

}
