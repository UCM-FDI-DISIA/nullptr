#include "Player.h"
#include "../core/SDLApplication.h"

Player::Player(SDLApplication* _game, Camera* _camera) {
	transform = addComponent<Transform>(PLAYER_INITIAL_POSITION, PLAYER_INITIAL_VELOCITY, PLAYER_INITIAL_WIDTH, PLAYER_INITIAL_HEIGHT, PLAYER_INITIAL_ROTATION);
	image = addComponent<Image>(_game->getTexture("Player"), _camera->getComponent<Transform>());
	playerMovementComponent = addComponent<PlayerMovementComponent>();
	cardComponent = addComponent<CardComponent>();
	_camera->startFollowObject(this);
}