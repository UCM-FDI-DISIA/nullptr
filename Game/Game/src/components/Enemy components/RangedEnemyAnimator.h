#pragma once
#include "../../sdlutils/SDLUtils.h"
#include "../../sdlutils/InputHandler.h"
#include "../General Components/CharacterAnimator.h"
class RangedEnemyAnimator : public CharacterAnimator {
private:
	bool attacking() {
		return ih().isKeyDown(SDLK_p);
	}
public:
	RangedEnemyAnimator() :
		CharacterAnimator(&sdlutils().images().at(RANGED_ENEMY_TEXTURE_KEY),
			RANGED_ENEMY_SPRITE_WIDTH, RANGED_ENEMY_SPRITE_HEIGHT,
			RANGED_ENEMY_SPRITE_ROWS, RANGED_ENEMY_SPRITE_COLS,
			RANGED_ENEMY_IDLE_ANIMATION, RANGED_ENEMY_MOVEMENT_ANIMATION) {
		addAttack(RANGED_ENEMY_ATTACK_ANIMATION, [&]() {return  attacking(); });
	}
};

