#include "Cards.h"
#include "Hitbox.h"

void SpearCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where)
{
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
	float rotation = Vector2D(1, 0).angle(dir);

	Hitbox::HitboxData data = { playerPos + dir * 100, Vector2D(), rotation, 100, 30, Constant::getString("SPEAR_THRUST"), _grp_ENEMIES};

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, false, 0.06, data);
}

void SpearCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where)
{
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
	float rotation = Vector2D(1, 0).angle(dir);

	Hitbox::HitboxData data = { playerPos, dir * Constant::getFloat("THROWN_SPEAR_SPEED"), rotation, 100, 30, Constant::getString("SPEAR_THRUST"), _grp_ENEMIES};

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, true, true, 10, data);

	remainingUses = 0;
}