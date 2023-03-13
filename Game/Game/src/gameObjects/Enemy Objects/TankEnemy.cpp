#include "TankEnemy.h"

void TankEnemy::initGameObject(Vector2D pos, int life, Player* player) {
	addComponent<Transform>(pos, Vector2D(0, 0), ENEMY_WIDTH, ENEMY_HEIGHT, 0);
	addComponent<CharacterAnimator>(SDLApplication::getTexture(TANK_ENEMY_TEXTURE_KEY),TANK_ENEMY_SPRITE_WIDTH,TANK_ENEMY_SPRITE_HEIGHT, 
		TANK_ENEMY_SPRITE_ROWS,TANK_ENEMY_SPRITE_COLS,TANK_ENEMY_IDLE_ANIMATION, TANK_ENEMY_MOVEMENT_ANIMATION);
	addComponent<ColliderComponent>(_grp_PLAYER);
	addComponent<TankBehaviour>(TANK_SPEED, TANK_ATTACK_DAMAGE, TANK_STOP_TIME, TANK_ATTACK_TIME, player);
	addComponent<HealthComponent>(life);
}