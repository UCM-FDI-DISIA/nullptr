#include "Cards.h"
#include "Hitbox.h"

void SpearCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where)
{
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
	float rotation = Vector2D(1, 0).angle(dir);

	Hitbox::HitboxData data = { playerPos + dir * 100, VECTOR_ZERO, rotation, 100, 30, "null", _grp_ENEMIES };

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, false, 0.06, data);


	auto spearAnim = where->addGameObject<GameObject>();

	auto spritePosition = playerPos + dir * 100 -Vector2D(40, 0);
	spearAnim->addComponent<Transform>(spritePosition, VECTOR_ZERO, 100, 30, rotation);
	auto anim = spearAnim->addComponent<Animator>(SDLApplication::getTexture("SpearThrustAnim"), 100, 30, 1, 12);
	anim->createAnim("SpearThrust", Animation(0, 11, 15, 1));
	anim->play("SpearThrust");
	spearAnim->addComponent<LifeTimeComponent>(1);

}

void SpearCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where)
{
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
	float rotation = Vector2D(1, 0).angle(dir);

	Hitbox::HitboxData data = { playerPos, dir * THROWN_SPEAR_SPEED, rotation, 100, 30, "SpearSkill", _grp_ENEMIES };

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, true, true, 10, data);

	remainingUses = 0;
}