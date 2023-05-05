#pragma once
#include "../../sdlutils/SDLUtils.h"
#include "../../sdlutils/InputHandler.h"
#include "../General Components/CharacterAnimator.h"
#include "BossBehaviour.h"
class BossAnimator : public CharacterAnimator
{
private:
	BossBehaviour* _bhvr;
	


public:
	// Llama al constructor del padre con las animaciones correspondientes y añade la de ataque
	BossAnimator(string txtr_key, int sprtW, int sprtH, int rws, int cols, Animation idle);
	// Recoge un puntero a RangeBehaviour
	void initComponent();
};


