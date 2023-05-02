#include "Cards.h"
#include "../../sdlutils/Texture.h"
#include "../Card Objects/Hitbox.h"
#include <iostream>

// Crea un gObj Slash en la dirección que apunta el jugador
void TorchCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {

	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
	float rotation = Vector2D(1, 0).angle(dir);

	Hitbox::HitboxData data = { playerPos + dir * 100, VECTOR_ZERO, rotation, 100, 120, "null", _grp_ENEMIES};
	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage, false, 4, StatusComponent::BURNED,  0.06, data, Vector2D(-1, -1), playerPos);

	auto slashAnim = where->addGameObject<GameObject>();

	auto spritePosition = playerPos + dir * 100 - Vector2D(PLAYER_SPRITE_WIDTH * 2, PLAYER_SPRITE_HEIGHT * 3);
	slashAnim->addComponent<Transform>(spritePosition, VECTOR_ZERO, 100, 200, rotation);
	auto anim = slashAnim->addComponent<Animator>(SDLApplication::getTexture("TorchSlash"), 96, 192, 1, 9);
	anim->createAnim("TorchSlash", Animation(0, 8, 20, 1));
	anim->play("TorchSlash");
	slashAnim->addComponent<LifeTimeComponent>(0.4);
}

// Crea un gObj cura en el centro del jugador
void TorchCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Hitbox::HitboxData data = { playerPos, VECTOR_ZERO, 0,TORCH_SIZE_HEAL, TORCH_SIZE_HEAL, HEAL_AREA, _grp_PLAYER };

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, 5, 0.5, data, 6);

	remainingUses = 0;
}
