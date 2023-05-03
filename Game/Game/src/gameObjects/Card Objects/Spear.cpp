#include "Cards.h"
#include "Hitbox.h"

void SpearCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where)
{
	Mix_PlayChannelTimed(-1, attackSound->getChunk(), 0, -1);
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
	float rotation = Vector2D(1, 0).angle(dir);

	Hitbox::HitboxData data = { playerPos + dir * 100, VECTOR_ZERO, rotation, 100, 30, "null", _grp_ENEMIES };

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, 0.2, data, Vector2D(-1,-1), nullptr, playerPos);


	auto spearAnim = where->addGameObject<GameObject>();

	auto spritePosition = playerPos + dir * 100;
	spearAnim->addComponent<Transform>(spritePosition - Vector2D(50, 15), VECTOR_ZERO, 100, 30, rotation);
	auto anim = spearAnim->addComponent<Animator>(SDLApplication::getTexture("SpearThrustAnim"), 100, 30, 1, 12);
	anim->createAnim("SpearThrust", Animation(0, 11, 100, 1));
	anim->play("SpearThrust");
	spearAnim->addComponent<LifeTimeComponent>(0.2);

}

void SpearCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where)
{
	Mix_PlayChannelTimed(-1, attackSound->getChunk(), 0, -1);
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
	float rotation = Vector2D(1, 0).angle(dir);

	Hitbox::HitboxData data = { playerPos, dir * THROWN_SPEAR_SPEED, rotation, 100, 30, "SpearSkill", _grp_ENEMIES };

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, 10, data, Vector2D(-1, -1), nullptr, playerPos);

	remainingUses = 0;
}