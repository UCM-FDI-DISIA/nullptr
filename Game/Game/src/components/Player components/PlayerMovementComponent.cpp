#include "PlayerMovementComponent.h"
#include "../../sdlutils/InputHandler.h"
#include "../../core/SDLApplication.h"
#include "../../data/PlayerData.h"

PlayerMovementComponent::PlayerMovementComponent() :transform(nullptr){}

void PlayerMovementComponent::initComponent() {
	transform = gObj->getComponent<Transform>();
	playerSpeed = PlayerData::instance()->getPlayerMoveSpeed();
}

void PlayerMovementComponent::handleInput() {
	Vector2D vel(0, 0);
	Vector2D pos =transform->getPos();

	// Izquierda
	if (pos.getX()>Constant::getFloat("PLAYER_INITIAL_WIDTH") && InputHandler::instance()->isKeyDown(SDLK_a)) {
		vel = vel + Vector2D(-1, 0);
	}
	// Derecha
	if (pos.getX()<Constant::getFloat("FLOOR_WIDTH") - Constant::getFloat("PLAYER_INITIAL_WIDTH") && InputHandler::instance()->isKeyDown(SDLK_d)) {
		vel = vel + Vector2D(1, 0);
	}
	// Arriba
	if (pos.getY()>0-Constant::getFloat("PLAYER_INITIAL_HEIGHT") / 3 && InputHandler::instance()->isKeyDown(SDLK_w)) {
		vel = vel + Vector2D(0, -1);
	}
	// Abajo
	if (pos.getY()<Constant::getFloat("FLOOR_HEIGHT") - Constant::getFloat("PLAYER_INITIAL_HEIGHT") && InputHandler::instance()->isKeyDown(SDLK_s)) {
		vel = vel + Vector2D(0, 1);
	}

	if(vel.magnitude()!=0)
	vel = vel / vel.magnitude();
	vel = vel * playerSpeed;
	transform->setVel(vel);

	// Activar la pausa lanzando su estado
	if (InputHandler::instance()->isKeyJustDown(SDLK_ESCAPE)) {
		SDLApplication::pauseGame();
	}
}

void PlayerMovementComponent::setPlayerSpeed(float newSpeed) {
	playerSpeed = newSpeed;
}