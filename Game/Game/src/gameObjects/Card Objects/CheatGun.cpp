#include "Cards.h"
#include "../Card Objects/Hitbox.h"
#include "../../components/Card Components/FollowEnemyComponent.h"
void CheatGunCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where)
{
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());

	dir = dir.normalize();

	Hitbox::HitboxData data = { playerPos, dir * BULLET_SPEED, 0, 30, 30, BULLET, _grp_ENEMIES };

	GameObject* Bullet = where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, true, false, 10, data);
	Bullet->addComponent<FollowEnemyComponent>(1);
}

void CheatGunCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where)
{

}
