#include "Player.h"
#include "../../core/SDLApplication.h"

// Crea los componentes del jugador
void Player::initGameObject() {
	transform = addComponent<Transform>(PLAYER_INITIAL_POSITION, PLAYER_INITIAL_VELOCITY, PLAYER_INITIAL_WIDTH, PLAYER_INITIAL_HEIGHT, PLAYER_INITIAL_ROTATION);
	playerMovementComponent = addComponent<PlayerMovementComponent>();
	cardComponent = addComponent<CardComponent>();
	health = addComponent<HealthComponent>(PlayerData::instance()->getMaxHP(), true);
	animator = addComponent<PlayerAnimator>(PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, PLAYER_SPRITE_ROWS, PLAYER_SPRITE_COLS);
}