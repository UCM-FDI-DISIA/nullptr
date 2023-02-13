#include "Player.h"
#include "../core/SDLApplication.h"

Player::Player(SDLApplication* _game) {
	addComponent<Transform>(Vector2D(WIN_WIDTH / 2, WIN_HEIGHT / 2), Vector2D(0, 0), WIN_WIDTH / 10, WIN_HEIGHT / 10, 0);
	addComponent<Image>(_game->getTexture("Player"));
	addComponent<PlayerMovementComponent>();
}

Player::Player(SDLApplication* _game, const Vector2D& _center) {
	cout << _center.getX() << " " << _center.getY() << endl;
	addComponent<Transform>(Vector2D(WIN_WIDTH / 2, WIN_HEIGHT / 2), Vector2D(0, 0), WIN_WIDTH / 10, WIN_HEIGHT / 10, 0, _center);
	addComponent<Image>(_game->getTexture("Player"));
	addComponent<PlayerMovementComponent>();
}