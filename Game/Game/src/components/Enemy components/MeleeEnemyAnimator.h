#pragma once
#include "../../sdlutils/SDLUtils.h"
#include "../../sdlutils/InputHandler.h"
#include "../General Components/CharacterAnimator.h"
#include "MeleeBehaviour.h"
class MeleeEnemyAnimator : public CharacterAnimator {
private:
	MeleeBehaviour* bhvr_;

	// Determina cuándo el enemigo está atacando
	inline bool attacking() {
		return bhvr_->isAttacking() || playingAttack();
	}
public:
	// Llama al constructor del padre con las animaciones correspondientes y añade la de ataque
	MeleeEnemyAnimator();
	// Recoge un puntero a MeleeBehaviour
	void initComponent();
};

