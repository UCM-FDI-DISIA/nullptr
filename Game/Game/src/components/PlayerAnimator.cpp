#include "PlayerAnimator.h"

void PlayerAnimator::initComponent() {
	Animator::initComponent();
	transform = gObj->getComponent<Transform>();
	if (gStt != nullptr) {
		createAnim(PLAYER_IDLE, PLAYER_IDLE_INITIAL_FRAME, PLAYER_IDLE_FINAL_FRAME, PLAYER_IDLE_FRAME_RATE, -1);
		createAnim(PLAYER_MOVE, PLAYER_MOVE_INITIAL_FRAME, PLAYER_MOVE_FINAL_FRAME, PLAYER_MOVE_FRAME_RATE, -1);

		// Se anima el estado idle por predeterminado
		play(PLAYER_IDLE);
	}
}

void PlayerAnimator::update() {
	Animator::update();

	if (transform != nullptr) {
		if (transform->getVel().getX() < 0 || transform->getVel().getX() > 0 || transform->getVel().getY() < 0 || transform->getVel().getY() > 0) {
			if (currentAnimationKey() != PLAYER_MOVE) {
				play(PLAYER_MOVE);
			}
		}
		else if (currentAnimationKey() != PLAYER_IDLE) {
			play(PLAYER_IDLE);
		}

		if (transform->getVel().getX() > 0) {
			flipNone();
		}
		else if (transform->getVel().getX() < 0) {
			flipHorizontal();
		}		
	}
}