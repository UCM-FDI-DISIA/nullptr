#include "Cards.h"
#include "Bomb.h"
#include "FlashBang.h"


void PulgaCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where)
{
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());

	dir = dir.normalize();

	where->addGameObject<Bomb>(_grp_PLYR_ATTACK, playerPos, dir, damage * attackMult, where, _grp_ENEMIES);
}

void PulgaCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where)
{
	where->addGameObject<FlashBang>(_grp_PLYR_ATTACK, playerPos, where, remainingUses, _grp_ENEMIES);
}
