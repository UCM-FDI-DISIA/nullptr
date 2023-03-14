#include "PlayerAnimator.h"
#include "../../gameObjects/GameObject.h"
#include "../../components/General Components/Transform.h"
#include "../../sdlutils/InputHandler.h"

// Constructora
PlayerAnimator::PlayerAnimator(Texture* _texture, int _w, int _h, int _r, int _c) :
	CharacterAnimator(_texture, _w, _h, _r, _c,
		Animation(PLAYER_IDLE_INITIAL_FRAME, PLAYER_IDLE_FINAL_FRAME, PLAYER_IDLE_FRAME_RATE, -1),
		Animation(PLAYER_MOVE_INITIAL_FRAME, PLAYER_MOVE_FINAL_FRAME, PLAYER_MOVE_FRAME_RATE, -1)) {

	this->addAction("attackMoving", Animation(PLAYER_ATTACK_MOVE_INITIAL_FRAME, PLAYER_ATTACK_MOVE_FINAL_FRAME, PLAYER_ATTACK_MOVE_FRAME_RATE, 1), [this]() {
		return isPlaying("attackMoving") || moving() && InputHandler::instance()->getMouseButtonState(InputHandler::LEFT);
		});

	this->addAction("attackIdle", Animation(PLAYER_ATTACK_IDLE_INITIAL_FRAME, PLAYER_ATTACK_IDLE_FINAL_FRAME, PLAYER_ATTACK_IDLE_FRAME_RATE, 1), [this]() {
		return isPlaying("attackIdle") || !moving() && InputHandler::instance()->getMouseButtonState(InputHandler::LEFT);
		});

	this->addAction("skillMoving", Animation(PLAYER_SKILL_MOVE_INITIAL_FRAME, PLAYER_SKILL_MOVE_FINAL_FRAME, PLAYER_SKILL_MOVE_FRAME_RATE, 1), [this]() {
		return isPlaying("skillMoving") || moving() && InputHandler::instance()->getMouseButtonState(InputHandler::RIGHT);
		});

	this->addAction("skillIdle", Animation(PLAYER_SKILL_IDLE_INITIAL_FRAME, PLAYER_SKILL_IDLE_FINAL_FRAME, PLAYER_SKILL_IDLE_FRAME_RATE, 1), [this]() {
		return isPlaying("skillIdle") || !moving() && InputHandler::instance()->getMouseButtonState(InputHandler::RIGHT);
		});

}


