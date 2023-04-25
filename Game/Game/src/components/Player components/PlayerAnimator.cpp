#include "PlayerAnimator.h"
#include "../../gameObjects/GameObject.h"
#include "../../components/General Components/Transform.h"
#include "../../sdlutils/InputHandler.h"
#include "../../core/SDLApplication.h"

// Constructora
PlayerAnimator::PlayerAnimator(int _w, int _h, int _r, int _c) :
	CharacterAnimator(SDLApplication::getTexture(Constant::getTextureName("PLAYER")), _w, _h, _r, _c,
		Animation(Constant::getInt("PLAYER_IDLE_INITIAL_FRAME"), Constant::getInt("PLAYER_IDLE_FINAL_FRAME"), Constant::getInt("PLAYER_IDLE_FRAME_RATE"), -1),
		Animation(Constant::getInt("PLAYER_MOVE_INITIAL_FRAME"), Constant::getInt("PLAYER_MOVE_FINAL_FRAME"), Constant::getInt("PLAYER_MOVE_FRAME_RATE"), -1)) {

	this->addAction(Constant::getString("CHARACTER_ATTACK_MOVE_KEY"), Animation(Constant::getInt("PLAYER_ATTACK_MOVE_INITIAL_FRAME"), Constant::getInt("PLAYER_ATTACK_MOVE_FINAL_FRAME"), Constant::getInt("PLAYER_ATTACK_MOVE_FRAME_RATE"), 1), [this]() {
		return moving() && (isPlaying(Constant::getString("CHARACTER_ATTACK_MOVE_KEY")) || isPlaying(Constant::getString("CHARACTER_ATTACK_IDLE_KEY")) || InputHandler::instance()->getMouseButtonState(InputHandler::LEFT));
		});
	this->addAction(Constant::getString("CHARACTER_ATTACK_IDLE_KEY"), Animation(Constant::getInt("PLAYER_ATTACK_IDLE_INITIAL_FRAME"), Constant::getInt("PLAYER_ATTACK_IDLE_FINAL_FRAME"), Constant::getInt("PLAYER_ATTACK_IDLE_FRAME_RATE"), 1), [this]() {
		return !moving() && (isPlaying(Constant::getString("CHARACTER_ATTACK_IDLE_KEY")) || isPlaying(Constant::getString("CHARACTER_ATTACK_MOVE_KEY")) || InputHandler::instance()->getMouseButtonState(InputHandler::LEFT));
		});

	this->linkAnimations(Constant::getString("CHARACTER_ATTACK_IDLE_KEY"), Constant::getString("CHARACTER_ATTACK_MOVE_KEY"));

	this->addAction(Constant::getString("CHARACTER_SKILL_MOVE_KEY"), Animation(Constant::getInt("PLAYER_SKILL_MOVE_INITIAL_FRAME"), Constant::getInt("PLAYER_SKILL_MOVE_FINAL_FRAME"), Constant::getInt("PLAYER_SKILL_MOVE_FRAME_RATE"), 1), [this]() {
		return moving() && (isPlaying(Constant::getString("CHARACTER_SKILL_MOVE_KEY")) || isPlaying(Constant::getString("CHARACTER_SKILL_IDLE_KEY")) || InputHandler::instance()->getMouseButtonState(InputHandler::RIGHT));
		});

	this->addAction(Constant::getString("CHARACTER_SKILL_IDLE_KEY"), Animation(Constant::getInt("PLAYER_SKILL_IDLE_INITIAL_FRAME"), Constant::getInt("PLAYER_SKILL_IDLE_FINAL_FRAME"), Constant::getInt("PLAYER_SKILL_IDLE_FRAME_RATE"), 1), [this]() {
		return !moving() && (isPlaying(Constant::getString("CHARACTER_SKILL_IDLE_KEY")) || isPlaying(Constant::getString("CHARACTER_SKILL_MOVE_KEY")) || InputHandler::instance()->getMouseButtonState(InputHandler::RIGHT));
		});

	this->linkAnimations(Constant::getString("CHARACTER_SKILL_IDLE_KEY"), Constant::getString("CHARACTER_SKILL_MOVE_KEY"));

	this->addAction(Constant::getString("CHARACTER_DEATH_KEY"), Animation(Constant::getInt("PLAYER_DEATH_INITAL_FRAME"), Constant::getInt("PLAYER_DEATH_FINAL_FRAME"), Constant::getInt("PLAYER_DEATH_FRAME_RATE"), 1), [this]() {
		return isPlaying(Constant::getString("CHARACTER_DEATH_KEY")) || gObj->getComponent<HealthComponent>()->getLife() <= 0;
		});
}

// Hace el update del padre y llama al metodo OnPlayerDies al terminar la animacion de muerte
void PlayerAnimator::update() {
	CharacterAnimator::update();
	if (isCurrentAnimation(Constant::getString("CHARACTER_DEATH_KEY")) && animationComplete()) {
		static_cast<BattleScene*>(gStt)->changeToGameOverScene();
	}
}