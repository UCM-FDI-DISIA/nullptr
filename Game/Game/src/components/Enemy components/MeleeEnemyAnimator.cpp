#include "MeleeEnemyAnimator.h"

// Llama al constructor del padre con las animaciones correspondientes y añade la de ataque
MeleeEnemyAnimator::MeleeEnemyAnimator() :
	CharacterAnimator(&sdlutils().images().at(MELEE_ENEMY_TEXTURE_KEY),
		MELEE_ENEMY_SPRITE_WIDTH, MELEE_ENEMY_SPRITE_HEIGHT,
		MELEE_ENEMY_SPRITE_ROWS, MELEE_ENEMY_SPRITE_COLS,
		MELEE_ENEMY_IDLE_ANIMATION, MELEE_ENEMY_MOVEMENT_ANIMATION), bhvr_(nullptr) {
	addAttack(MELEE_ENEMY_ATTACK_ANIMATION, [&]() { return attacking(); });
}

// Recoge un puntero a RangeBehaviour
void MeleeEnemyAnimator::initComponent() {
	CharacterAnimator::initComponent();
	bhvr_ = gObj->getComponent<MeleeBehaviour>();
	assert(bhvr_ != nullptr);
}