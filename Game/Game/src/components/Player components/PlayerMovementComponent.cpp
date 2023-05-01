#include "PlayerMovementComponent.h"
#include "../../sdlutils/InputHandler.h"
#include "../../core/SDLApplication.h"
#include "../../data/PlayerData.h"

PlayerMovementComponent::PlayerMovementComponent() :transform(nullptr), dashDuration(0) , gmCtrl_(gmCtrl()){}

void PlayerMovementComponent::initComponent() {
	transform = gObj->getComponent<Transform>();
	playerSpeed = PlayerData::instance()->getPlayerMoveSpeed();
}

void PlayerMovementComponent::setDirection(Vector2D dir) {
	// L�mites
	Vector2D pos = transform->getPos();
	if (pos.getX() < PLAYER_INITIAL_WIDTH) transform->setX(PLAYER_INITIAL_WIDTH);
	else if (pos.getX() > FLOOR_WIDTH - PLAYER_INITIAL_WIDTH) transform->setX(FLOOR_WIDTH - PLAYER_INITIAL_WIDTH);

	if (pos.getY() < 0 - PLAYER_INITIAL_HEIGHT / 3) transform->setY(0 - PLAYER_INITIAL_HEIGHT / 3);
	else if (pos.getY() > FLOOR_HEIGHT - PLAYER_INITIAL_HEIGHT) transform->setY(FLOOR_HEIGHT - PLAYER_INITIAL_HEIGHT);

	moveDir = dir.normalize() * playerSpeed;

	// Activar la pausa lanzando su estado
	if (InputHandler::instance()->isKeyJustDown(SDLK_ESCAPE)) {
		SDLApplication::pauseGame();
	}
}

void PlayerMovementComponent::update()
{
	if (dashDuration <= 0) transform->setVel(moveDir);
	else dashDuration -= SDLApplication::instance()->getDeltaTimeSeconds();
}

void PlayerMovementComponent::setPlayerSpeed(float newSpeed) {
	playerSpeed = newSpeed;
}

void PlayerMovementComponent::dash(Vector2D dir) {
	Vector2D vel = dir * DASH_SPEED;
	dashDuration = DASH_DURATION;
	transform->setVel(vel);
}