#pragma once
#ifndef PLAYER_ANIMATOR_H_
#define PLAYER_ANIMATOR_H_
#include "../General Components/CharacterAnimator.h"
#include "../../gameObjects/GameObject.h"

class PlayerAnimator : public CharacterAnimator {
public:

	// Constructora
	PlayerAnimator(Texture* _texture, int _w, int _h, int _r, int _c) : 
		CharacterAnimator(_texture, _w, _h, _r, _c, 
			Animation(PLAYER_IDLE_INITIAL_FRAME, PLAYER_IDLE_FINAL_FRAME, PLAYER_IDLE_FRAME_RATE, -1),
			Animation(PLAYER_MOVE_INITIAL_FRAME, PLAYER_MOVE_FINAL_FRAME, PLAYER_MOVE_FRAME_RATE, -1)) {}
};
#endif // !PLAYER_ANIMATOR_H_
