#include "OnDeath.h"

void OnDeath::initComponent() {
	enemyData = gObj->getComponent<Transform>();
}

void OnDeath::death() {
	for (int i = 0; i < numEter; i++) {
		//where->addGameObject();
	}
	for (int i = 0; i < numMana; i++) {
		where->addGameObject();
	}
}