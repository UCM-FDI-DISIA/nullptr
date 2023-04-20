#include "Cards.h"
#include "../Card Objects/Hitbox.h"

// Crea un gObj Slash en la direcci�n que apunta el jugador
void SwordCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
	float rotation = Vector2D(1, 0).angle(dir);

	Hitbox::HitboxData data = { playerPos + dir * 100, VECTOR_ZERO, rotation, 200, 100, "null", _grp_ENEMIES };

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, false, 0.06, data);

	auto slashAnim = where->addGameObject<GameObject>();

	auto spritePosition = playerPos + dir * 100 -Vector2D(PLAYER_SPRITE_WIDTH * 2, PLAYER_SPRITE_HEIGHT * 3);
	slashAnim->addComponent<Transform>(spritePosition, VECTOR_ZERO, 100, 200, rotation);
	auto anim = slashAnim->addComponent<Animator>(SDLApplication::getTexture("NewSwordSlash"), 96, 192, 1, 9);
	anim->createAnim("SwordSlash", Animation(0, 8, 10, 1));
	anim->play("SwordSlash");
	slashAnim->addComponent<LifeTimeComponent>(1);

}

// Crea un gObj Spin en el centro del jugador
void SwordCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	
	Hitbox::HitboxData  data = { playerPos, VECTOR_ZERO, 0, 300, 300, "null", _grp_ENEMIES };

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, false, 0.1, data);

	auto spinAnim = where->addGameObject<GameObject>();
	spinAnim->addComponent<Transform>(playerPos - Vector2D(150, 150), VECTOR_ZERO, 300, 300);
	auto anim = spinAnim->addComponent<Animator>(SDLApplication::getTexture("NewSwordSpin"), 192, 192, 1, 8);
	anim->createAnim("SwordSpin", Animation(0, 7, 10, 1));
	anim->play("SwordSpin");
	spinAnim->addComponent<LifeTimeComponent>(1);


	remainingUses = 0;
}
