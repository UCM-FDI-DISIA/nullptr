#include "Cards.h"
#include "Hitbox.h"


void PulgaCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where)
{
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());

	dir = dir.normalize();
	float rot = where->getPointer()->getComponent<Transform>()->getRotation() - 90;

	Hitbox::HitboxData data = {playerPos, dir * BULLET_SPEED, rot, 10, 10, PULGA_BULLET, _grp_ENEMIES};

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, true, 3, StatusComponent::NONE, 240, 240, PULGA_EXPLOSION, where, data);
}

void PulgaCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where)
{
	Hitbox::HitboxData data = { playerPos, VECTOR_ZERO, 0, 800, 800, FLASH_BANG, _grp_ENEMIES };

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, remainingUses, StatusComponent::CONFUSED, 0.5, data);

	remainingUses = 0;
}
