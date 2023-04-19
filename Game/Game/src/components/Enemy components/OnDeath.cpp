#include "OnDeath.h"

void OnDeath::initComponent() {
	enemyTransform = gObj->getComponent<Transform>();
}

void OnDeath::death() {
	for (int i = 0; i < numEter; i++) {
		gStt->addGameObject<SpacialEter>(enemyTransform->getPos().getX() + (sdlutils().rand().nextInt(-50, 50)), enemyTransform->getPos().getY() - 20, playerTransform);
	}
	for (int i = 0; i < numMana; i++) {
		gStt->addGameObject<Mana>(_grp_MANA, enemyTransform->getPos());
	}
	dynamic_cast<BattleScene*>(gStt)->getTracker()->onEnemyKilled(gObj);
	
}