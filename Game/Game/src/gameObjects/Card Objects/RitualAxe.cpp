#include "Cards.h"
#include "../Card Objects/Hitbox.h"

void RitualAxeCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where)
{
	Mix_PlayChannelTimed(-1, attackSound->getChunk(), 0, -1);
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
	float rotation = Vector2D(1, 0).angle(dir);

	Hitbox::HitboxData data = { playerPos + dir * 100, VECTOR_ZERO, rotation, 200, 100, SWORD_SLASH, _grp_ENEMIES };

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, (damage + damage * enemiesKilled) * attackMult, false, 0.06, data, Vector2D(-1,-1), this, playerPos);
}

void RitualAxeCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where)
{
	where->getPlayer()->getComponent<HealthComponent>()->heal(2 * enemiesKilled);
	remainingUses = 0;
}

void RitualAxeCard::enemieKilled()
{
	enemiesKilled++;
}
