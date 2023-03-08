#include "RangedEnemyAnimator.h"

// Llama al constructor del padre con las animaciones correspondientes y añade la de ataque
RangedEnemyAnimator::RangedEnemyAnimator() :
	CharacterAnimator(&sdlutils().images().at(RANGED_ENEMY_TEXTURE_KEY),
		RANGED_ENEMY_SPRITE_WIDTH, RANGED_ENEMY_SPRITE_HEIGHT,
		RANGED_ENEMY_SPRITE_ROWS, RANGED_ENEMY_SPRITE_COLS,
		RANGED_ENEMY_IDLE_ANIMATION, RANGED_ENEMY_MOVEMENT_ANIMATION), bhvr_(nullptr) {
	addAttack(RANGED_ENEMY_ATTACK_ANIMATION, [&]() { return attacking(); });
}

// Recoge un puntero a RangeBehaviour
void RangedEnemyAnimator::initComponent() {
	 CharacterAnimator::initComponent();
	 bhvr_ = gObj->getComponent<RangeBehaviour>();
	 assert(bhvr_ != nullptr);
}