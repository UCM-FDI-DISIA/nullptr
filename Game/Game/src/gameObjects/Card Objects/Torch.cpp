#include "Cards.h"
#include "../../sdlutils/Texture.h"
#include "../Card Objects/Hitbox.h"
#include <iostream>

// Crea un gObj Slash en la direcci�n que apunta el jugador
void TorchCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {

	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
	float rotation = Vector2D(1, 0).angle(dir);

	Hitbox::HitboxData data = { playerPos + dir * 100, Vector2D(), rotation, 200, 100, Constant::getString("SWORD_SLASH"), _grp_ENEMIES};
	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage, false, false, 4, StatusComponent::BURNED,  0.06, data);
}

// Crea un gObj cura en el centro del jugador
void TorchCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Hitbox::HitboxData data = { playerPos, Vector2D(), 0, Constant::getFloat("TORCH_SIZE_HEAL"), Constant::getFloat("TORCH_SIZE_HEAL"), Constant::getString("HEAL_AREA"), _grp_PLAYER};

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, 5, 0.5, data, 6);

	remainingUses = 0;
}
