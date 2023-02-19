#include "Player.h"
#include "../core/SDLApplication.h"

// Crea los componentes del jugador
void Player::initGameObject() {
	transform = addComponent<Transform>(PLAYER_INITIAL_POSITION, PLAYER_INITIAL_VELOCITY, PLAYER_INITIAL_WIDTH, PLAYER_INITIAL_HEIGHT, PLAYER_INITIAL_ROTATION);
	image = addComponent<Image>(SDLApplication::getTexture("Player"));
	playerMovementComponent = addComponent<PlayerMovementComponent>();
	cardComponent = addComponent<CardComponent>();

	_myScene = dynamic_cast<BattleScene*>(gStt);
}