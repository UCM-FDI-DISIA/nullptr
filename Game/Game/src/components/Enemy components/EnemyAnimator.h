#pragma once
#include "../../sdlutils/SDLUtils.h"
#include "../../sdlutils/InputHandler.h"
#include "../General Components/CharacterAnimator.h"
#include "EnemyBehaviour.h"
class EnemyAnimator: public CharacterAnimator
{
private:
	EnemyBehaviour* _bhvr;
	// Determina cuándo el enemigo está atacando
	inline bool attacking() {
		return _bhvr->isAttacking() || playingAttack();
	}
public:
	// Llama al constructor del padre con las animaciones correspondientes y añade la de ataque
	EnemyAnimator(string txtr_key, int sprtW, int sprtH, int rws, int cols, Animation idle, Animation mvment, Animation atck);
	// Recoge un puntero a RangeBehaviour
	void initComponent();
};
