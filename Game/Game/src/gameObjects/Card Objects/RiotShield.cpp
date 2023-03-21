#include "Cards.h"
#include "../../sdlutils/Texture.h"
#include "../Card Objects/Hitbox.h"
#include <iostream>

// Crea un gObj Slash en la dirección que apunta el jugador
void RiotShieldCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {

	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
	float rotation = Vector2D(1, 0).angle(dir);

	Hitbox::HitboxData data = { playerPos + dir * 100, VECTOR_ZERO, rotation, 200, 100, "SwordSlash", _grp_ENEMIES };

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, false, 0.06, data);;
}

// Crea un gObj proteger al jugador
// Crea un gObj para proteger al jugador
void RiotShieldCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
	float rotation = Vector2D(1, 0).angle(dir);

	Hitbox::HitboxData data = { playerPos + dir * 50, dir * SHIELD_SPEED, rotation, 200, 100, "SwordSlash", _grp_ENM_ATTACK };

	auto shield = where->addGameObject<Hitbox>(0.5, data);

	auto shieldTransform = shield->getComponent<Transform>();
	auto playerTransform = where->getPlayer()->getComponent<Transform>();

	auto shieldCollider = shield->getComponent<ColliderComponent>();
	shieldCollider->addFunction(std::bind(&RiotShieldCard::destroyBullet, this, std::placeholders::_1));


	//shield->addComponent<FollowComponent>(playerTransform);

	remainingUses = 0;
}

