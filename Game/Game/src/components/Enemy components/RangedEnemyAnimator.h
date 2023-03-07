#pragma once
#include "../../sdlutils/SDLUtils.h"
#include "../../sdlutils/InputHandler.h"
#include "../General Components/CharacterAnimator.h"
#include "RangeBehaviour.h"
class RangedEnemyAnimator : public CharacterAnimator {
private:
	RangeBehaviour* bhvr_;

	// Determina cuándo el enemigo está atacando
	inline bool attacking() {
		return bhvr_->isAttacking() || playingAttack();
	}
public:
	// Llama al constructor del padre con las animaciones correspondientes y añade la de ataque
	RangedEnemyAnimator();
	// Recoge un puntero a RangeBehaviour
	void initComponent();
};

