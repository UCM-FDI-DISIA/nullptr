#include "Cards.h"
#include "Hitbox.h"


void PulgaCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where)
{
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());

	dir = dir.normalize();

	Hitbox::HitboxData data = {playerPos, dir * Constant::getFloat("BULLET_SPEED"), 0, 16, 16, Constant::getString("BULLET"), _grp_ENEMIES};

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, true, 3, StatusComponent::NONE, 250, 250, Constant::getString("BULLET"), where, data);
}

void PulgaCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where)
{
	Hitbox::HitboxData data = { playerPos, Vector2D(), 0, 800, 800, Constant::getString("FLASH_BANG"), _grp_ENEMIES};

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, remainingUses, StatusComponent::CONFUSED, 0.5, data);

	remainingUses = 0;
}
