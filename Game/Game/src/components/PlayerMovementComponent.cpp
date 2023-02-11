#include "PlayerMovementComponent.h"
#include "../sdlutils/InputHandler.h"

PlayerMovementComponent::PlayerMovementComponent() :transform(nullptr){}

void PlayerMovementComponent::initComponent() {
	transform = gObj->getComponent<Transform>();
}

void PlayerMovementComponent::handleInput() {
	if (InputHandler::instance()->isKeyDown(SDLK_a)) {
		//Movimiento a la izquierda
		transform->setPos(Vector2D(transform->getPos() - Vector2D(playerSpeed, 0)));

	}else if (InputHandler::instance()->isKeyDown(SDLK_d)) {
		//Movimiento a la derecha
		transform->setPos(Vector2D(transform->getPos() + Vector2D(playerSpeed, 0)));

	}else if (InputHandler::instance()->isKeyDown(SDLK_w)) {
		//Movimiento hacia arriba
		transform->setPos(Vector2D(transform->getPos() - Vector2D(0, playerSpeed)));

	}else if (InputHandler::instance()->isKeyDown(SDLK_s)) {
		//Movimiento hacia abajo
		transform->setPos(Vector2D(transform->getPos() + Vector2D(0, playerSpeed)));

	}
}