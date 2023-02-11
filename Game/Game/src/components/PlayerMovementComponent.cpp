#include "PlayerMovementComponent.h"
#include "../sdlutils/InputHandler.h"

PlayerMovementComponent::PlayerMovementComponent() :transform(nullptr){}

void PlayerMovementComponent::initComponent() {
	transform = gObj->getComponent<Transform>();
}

void PlayerMovementComponent::handleInput() {
	if (InputHandler::instance()->isKeyDown(SDLK_a)) {
		//Movimiento a la izquierda
		transform->setVel(Vector2D(-playerSpeed, 0));
	}
	else if (InputHandler::instance()->isKeyUp(SDLK_a)) {
		transform->setVel(Vector2D());
	}

	if (InputHandler::instance()->isKeyDown(SDLK_d)) {
		//Movimiento a la derecha
		transform->setVel(Vector2D(playerSpeed, 0));
	}
	else if (InputHandler::instance()->isKeyUp(SDLK_d)) {
		transform->setVel(Vector2D());
	}

	if (InputHandler::instance()->isKeyDown(SDLK_w)) {
		//Movimiento hacia arriba
		transform->setVel(Vector2D(0,-playerSpeed));
	}
	else if (InputHandler::instance()->isKeyUp(SDLK_w)) {
		transform->setVel(Vector2D());
	}
	
	if (InputHandler::instance()->isKeyDown(SDLK_s)) {
		//Movimiento abajo
		transform->setVel(Vector2D(0,playerSpeed));
	}
	else if (InputHandler::instance()->isKeyUp(SDLK_s)) {
		transform->setVel(Vector2D());
	}
	
}