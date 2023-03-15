#include "OnDeath.h"

void OnDeath::initComponent() {
	enemyTransform = gObj->getComponent<Transform>();
}

void OnDeath::death() {
	for (int i = 0; i < numEter; i++) {
		
	}
	for (int i = 0; i < numMana; i++) {
		GameObject* mana = gStt->addGameObject<Mana>(_grp_MANA, enemyTransform->getPos());
	}
}