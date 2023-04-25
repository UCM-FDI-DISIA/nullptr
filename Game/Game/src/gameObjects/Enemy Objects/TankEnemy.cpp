#include "TankEnemy.h"
#include "../../components/General Components/StatusComponent.h"
void TankEnemy::initGameObject(Vector2D pos, int life, Player* player) {
	addComponent<Transform>(pos, Vector2D(), Constant::getInt("TANK_WIDTH"), Constant::getInt("ENEMY_HEIGHT"), 0);
	addComponent<ColliderComponent>(_grp_PLAYER);
	addComponent<TankBehaviour>(Constant::getFloat("TANK_SPEED"), Constant::getInt("TANK_ATTACK_DAMAGE"), Constant::getFloat("TANK_STOP_TIME"), Constant::getFloat("TANK_ATTACK_TIME"), player);
	addComponent<OnDeath>(3, 1,player->getComponent<Transform>());
	ColliderComponent* collider=addComponent<ColliderComponent>(_grp_PLAYER);
	collider->addFunction(getComponent<TankBehaviour>()->tankAttack());
	addComponent<HealthComponent>(life);
	addComponent<EnemyAnimator>(Constant::getString("TANK_ENEMY_TEXTURE_KEY"), Constant::getInt("TANK_ENEMY_SPRITE_WIDTH"), Constant::getInt("TANK_ENEMY_SPRITE_HEIGHT"),
		Constant::getInt("TANK_ENEMY_SPRITE_ROWS"), Constant::getInt("TANK_ENEMY_SPRITE_COLS"), Constant::getAnimation("TANK_ENEMY_IDLE_ANIMATION"), Constant::getAnimation("TANK_ENEMY_MOVEMENT_ANIMATION"), Constant::getAnimation("TANK_ENEMY_ATTACK_ANIMATION"));
	addComponent<ColliderComponent>(_grp_PLAYER);
	addComponent<StatusComponent>();
}