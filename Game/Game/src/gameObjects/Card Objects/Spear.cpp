#include "Cards.h"
#include "Hitbox.h"
#include "ThrownSpear.h"

void SpearCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where)
{
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();

	where->addGameObject<Hitbox>(playerPos, dir, where, damage * attackMult, SDLApplication::getTexture("SpearThrust"));
}

void SpearCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where)
{
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());

	dir = dir.normalize();

	where->addGameObject<ThrownSpear>(playerPos, dir, damage * attackMult, where->getEnemies());
}