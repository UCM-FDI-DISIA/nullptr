#include "Cards.h"
#include "../Card Objects/Hitbox.h"

// Crea un gObj Slash en la direcci�n que apunta el jugador
void SwordCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
	float rotation = Vector2D(1, 0).angle(dir);

	Hitbox::HitboxData data = {playerPos + dir * 100, VECTOR_ZERO, rotation, 200, 100, SWORD_SLASH, _grp_ENEMIES};

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, false, 0.06, data);

}

// Crea un gObj Spin en el centro del jugador
void SwordCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	
	Hitbox::HitboxData  data = { playerPos, VECTOR_ZERO, 0, 300, 300, "null", _grp_ENEMIES };

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, false, 0.1, data);

	auto slashAnim = where->addGameObject<GameObject>();
	slashAnim->addComponent<Transform>(playerPos - Vector2D(150, 150), VECTOR_ZERO, 300, 300);
	auto anim = slashAnim->addComponent<Animator>(SDLApplication::getTexture("NewSwordSpin"), 192, 192, 1, 8);
	anim->createAnim("SwordSpin", Animation(0, 7, 10, 1));
	anim->play("SwordSpin");
	slashAnim->addComponent<LifeTimeComponent>(1);


	remainingUses = 0;
}
