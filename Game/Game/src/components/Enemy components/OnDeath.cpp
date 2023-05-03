#include "OnDeath.h"

void OnDeath::initComponent() {
	enemyTransform = gObj->getComponent<Transform>();
	if (dynamic_cast<MeleeEnemy*>(gObj)) {
		deathSound= &sdlutils().soundEffects().at(MELEE_DEATH_SOUND);
		type = meleeEnemy;
	}
	else if (dynamic_cast<RangedEnemy*>(gObj)) {
		deathSound = &sdlutils().soundEffects().at(RANGED_DEATH_SOUND);
		type = rangedEnemy;
	}
	else if (dynamic_cast<TankEnemy*>(gObj)) {
		deathSound = &sdlutils().soundEffects().at(TANK_DEATH_SOUND);
		type = tankEnemy;
	}
	else if (dynamic_cast<AssasinEnemy*>(gObj)) {
		deathSound = &sdlutils().soundEffects().at(TANK_DEATH_SOUND);
		type = assasinEnemy;
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
	deathAnim();

	BattleScene* bS = dynamic_cast<BattleScene*>(gStt);
	bS->getTracker()->onEnemyKilled(gObj);
}

void OnDeath::deathAnim() {
	gStt->addGameObject<DeathAnimation>(_grp_GENERAL, enemyTransform->getPos(), type, enemyTransform->getVel().getX());
	GameObject* anim = gStt->addGameObject(_grp_GENERAL);
	anim->addComponent<Transform>(Vector2D(enemyTransform->getPos().getX() - 10, enemyTransform->getPos().getY() - 10), VECTOR_ZERO, enemyTransform->getWidth() * 1.2, enemyTransform->getHeight() * 1.5);
	anim->addComponent<Animator>(SDLApplication::getTexture("DeathAnim"), 40, 50, 2, 9);
	Animation map;
	map.startFrame = 0;
	map.endFrame = 17;
	map.backwards = false;
	map.frameRate = 24;
	map.repeat = 1;
	anim->getComponent<Animator>()->createAnim("death", map);
	anim->getComponent<Animator>()->play("death");
	anim->addComponent<LifeTimeComponent>(0.8);
}