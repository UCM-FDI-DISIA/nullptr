#include "StatsTrackComponent.h"
#include "../../core/SDLApplication.h"
#include "../Enemy components/RangeBehaviour.h"
#include "../../scenes/PostGameScene.h"

void StatsTrackComponent::update()
{
	if(timeCounting)
		time += SDLApplication::instance()->getDeltaTimeSeconds();
}

void StatsTrackComponent::onPlayerDamage(int dmg)
{
	damage += dmg;
}

void StatsTrackComponent::onEnemyKilled(GameObject* enemy)
{
	if (enemy->getComponent<MeleeBehaviour>())
		melee++;
	else if (enemy->getComponent<TankBehaviour>())
		tank++;
	else if (enemy->getComponent<RangeBehaviour>())
		ranged++;
}

void StatsTrackComponent::calculateMoney()
{
	int enemies = 2 * tank + melee + ranged;
	money = ((enemies * ENEMYFACTOR) - (damage * DAMAGEFACTOR)) / (time / MINTIME[PlayerData::instance()->getLevel()]);
}

void StatsTrackComponent::endTimeCouinting()
{
	timeCounting = false;
}

void StatsTrackComponent::startStatsScene()
{
	calculateMoney();
	SDLApplication::newScene<PostGameScene>(damage,melee,ranged,tank,money,time);
}
