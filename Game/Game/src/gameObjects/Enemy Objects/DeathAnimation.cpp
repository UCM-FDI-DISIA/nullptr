#include "DeathAnimation.h"

void DeathAnimation::initGameObject(Vector2D pos, int enemy) {
	if(enemy == 0){
		addComponent<Transform>(pos, Vector2D(0, 0), MELEE_ENEMY_WIDTH, MELEE_ENEMY_HEIGHT);
		addComponent<Image>(SDLApplication::getTexture("MeleeEnemyDeath"));
	}
	else if (enemy == 1) {
		addComponent<Transform>(pos, Vector2D(0, 0), RANGED_ENEMY_WIDTH, RANGED_ENEMY_HEIGHT);
		addComponent<Image>(SDLApplication::getTexture("RangedEnemyDeath"));
	}
	else if (enemy == 2) {
		addComponent<Transform>(pos, Vector2D(0, 0), TANK_WIDTH, TANK_HEIGHT);
		addComponent<Image>(SDLApplication::getTexture("TankEnemyDeath"));
	}
	else if (enemy == 3) {
		addComponent<Transform>(pos, Vector2D(0, 0), MELEE_ENEMY_WIDTH, MELEE_ENEMY_HEIGHT);
		addComponent<Image>(SDLApplication::getTexture("AssasinEnemyDeath"));
	}

	addComponent<LifeTimeComponent>(0.75);
}