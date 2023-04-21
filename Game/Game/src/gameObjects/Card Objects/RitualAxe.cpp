#include "Cards.h"
#include "../Card Objects/Hitbox.h"

void RitualAxeCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where)
{
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
	float rotation = Vector2D(1, 0).angle(dir);

	Hitbox::HitboxData data = { playerPos + dir * 100, Vector2D(), rotation, 200, 100, Constant::getString("SWORD_SLASH"), _grp_ENEMIES};

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, (damage + damage * enemiesKilled) * attackMult, false, false, 0.06, data, Vector2D(-1,-1), this);

	cout << "enemiesKilled: " + to_string(enemiesKilled) + "\n";
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
