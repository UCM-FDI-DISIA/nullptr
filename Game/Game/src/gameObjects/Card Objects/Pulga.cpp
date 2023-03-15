#include "Cards.h"
#include "Hitbox.h"


void PulgaCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where)
{
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());

	dir = dir.normalize();

	Hitbox::HitboxData data = {playerPos, dir * BULLET_SPEED, 0, 16, 16, "Bullet", _grp_ENEMIES};

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, true, 3, HitboxStatusComponent::NONE, 250, 250,"Bullet", where, data);
}

void PulgaCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where)
{
	Hitbox::HitboxData data = { playerPos, VECTOR_ZERO, 0, 800, 800, "FlashBang", _grp_ENEMIES };

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, remainingUses, HitboxStatusComponent::CONFUSED, 0.5, data);

	remainingUses = 0;
}
