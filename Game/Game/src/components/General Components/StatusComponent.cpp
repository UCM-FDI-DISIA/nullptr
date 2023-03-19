#include "StatusComponent.h"
#include "../../core/SDLApplication.h"
StatusComponent::StatusComponent() : aSecond(0), health(nullptr), enemyAI(nullptr)
{
	for (int i = 0; i < LAST_STATUS; i++) {
		statusMap.insert({ status(i),0 });
	}
}

void StatusComponent::initComponent()
{
	health = gObj->getComponent<HealthComponent>();
	enemyAI = gObj->getComponent<EnemyBehaviour>();
}

void StatusComponent::update()
{
	aSecond += SDLApplication::instance()->getDeltaTime();
	if (statusMap[BURNED] > 0 && aSecond >= 1000) {
		health->receiveDamage(BURN_DAMAGE);
	}
	if (enemyAI->isConfused() && statusMap[CONFUSED] <= 0) {
		enemyAI->setConfusion(false);
	}
	for (auto e : statusMap) {
		if(e.second > 0) e.second -= SDLApplication::instance()->getDeltaTimeSeconds();
	}
	if (aSecond >= 1000) aSecond = 0;
}

void StatusComponent::applyStatus(status stts, float duration)
{
	statusMap[stts] = duration;
	if (stts == CONFUSED) enemyAI->setConfusion(true);
}
