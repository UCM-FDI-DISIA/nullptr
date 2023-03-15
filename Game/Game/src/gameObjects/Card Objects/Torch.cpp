#include "Cards.h"
#include "../../sdlutils/Texture.h"
#include "../Card Objects/Hitbox.h"
#include <iostream>

// Crea un gObj Slash en la dirección que apunta el jugador
void Torch::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {

	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
	float rotation = Vector2D(1, 0).angle(dir);

	Hitbox::HitboxData data = { playerPos + dir * 100, VECTOR_ZERO, rotation, 200, 100, "SwordSlash", _grp_ENEMIES };
	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage, false, false, 5 , HitboxStatusComponent::Status::BURNED, 0.06, data);
}

// Crea un gObj cura en el centro del jugador
void Torch::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {

	Hitbox::HitboxData data = { playerPos, VECTOR_ZERO, 0, 800, 800, "FlashBang", _grp_ENEMIES };

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK,2, remainingUses, HitboxStatusComponent::HEALING, 0.5, data);

	remainingUses = 0;


	//where->addGameObject<SwordSpin>(playerPos, where, damage * remainingUses * attackMult);

}
