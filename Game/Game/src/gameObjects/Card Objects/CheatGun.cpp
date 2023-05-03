#include "Cards.h"
#include "../Card Objects/Hitbox.h"
#include "../../components/Card Components/FollowEnemyComponent.h"
void CheatGunCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where)
{
	Mix_PlayChannelTimed(-1, attackSound->getChunk(), 0, -1);
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());

	dir = dir.normalize();
	float rot = where->getPointer()->getComponent<Transform>()->getRotation() - 90;

	Hitbox::HitboxData data = { playerPos, dir * GUN_BULLET_SPEED, rot, 20, 10, BULLET, _grp_ENEMIES };

	GameObject* Bullet = where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, true, 10, data);
	Bullet->addComponent<FollowEnemyComponent>(0.5);
}

void CheatGunCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where)
{
	where->getPlayer()->getComponent<HealthComponent>()->setInvencibility(0.5 * remainingUses);
	remainingUses = 0;
}
