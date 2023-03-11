#include "OnDeath.h"

void OnDeath::initComponent() {
	enemyData = gObj->getComponent<Transform>();
}

void OnDeath::death() {
	for (int i = 0; i < numEter; i++) {
		
	}
	for (int i = 0; i < numMana; i++) {
		GameObject* mana = where->addGameObject<Mana>(_grp_PLAYER, enemyData->getPos());
	}
}