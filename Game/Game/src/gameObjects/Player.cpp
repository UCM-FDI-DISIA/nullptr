#include "Player.h"
#include "../core/SDLApplication.h"

// Crea los componentes del jugador
void Player::initGameObject() {
	transform = addComponent<Transform>(PLAYER_INITIAL_POSITION, PLAYER_INITIAL_VELOCITY, PLAYER_INITIAL_WIDTH, PLAYER_INITIAL_HEIGHT, PLAYER_INITIAL_ROTATION);
	playerMovementComponent = addComponent<PlayerMovementComponent>();
	cardComponent = addComponent<CardComponent>();
	health = addComponent<HealthComponent>(100);
	animator = addComponent<PlayerAnimator>(SDLApplication::getTexture("Player"), 36, 36, 2, 8);
}