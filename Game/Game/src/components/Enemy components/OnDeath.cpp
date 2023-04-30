#include "OnDeath.h"

void OnDeath::initComponent() {
	enemyTransform = gObj->getComponent<Transform>();
	if (dynamic_cast<MeleeEnemy*>(gObj)) {
		deathSound= &sdlutils().soundEffects().at(MELEE_DEATH_SOUND);
	}
	else if (dynamic_cast<RangedEnemy*>(gObj)) {
		deathSound = &sdlutils().soundEffects().at(RANGED_DEATH_SOUND);
	}
	else if (dynamic_cast<TankEnemy*>(gObj)) {
		deathSound = &sdlutils().soundEffects().at(TANK_DEATH_SOUND);
	}
}

void OnDeath::death() {
	Mix_PlayChannelTimed(-1, deathSound->getChunk(), 0,-1);
	for (int i = 0; i < numEter; i++) {
		gStt->addGameObject<SpacialEter>(enemyTransform->getPos().getX() + (sdlutils().rand().nextInt(-50, 50)), enemyTransform->getPos().getY() - 20, playerTransform);
	}
	for (int i = 0; i < numMana; i++) {
		gStt->addGameObject<Mana>(_grp_MANA, enemyTransform->getPos());
	}
	BattleScene* bS = dynamic_cast<BattleScene*>(gStt);
	bS->getTracker()->onEnemyKilled(gObj);
}