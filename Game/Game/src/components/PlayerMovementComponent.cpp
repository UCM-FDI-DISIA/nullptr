#include "PlayerMovementComponent.h"
#include "../sdlutils/InputHandler.h"

PlayerMovementComponent::PlayerMovementComponent() :transform(nullptr){}

void PlayerMovementComponent::initComponent() {
	transform = gObj->getComponent<Transform>();
}

void PlayerMovementComponent::handleInput() {
	Vector2D vel(0, 0);
	if (InputHandler::instance()->isKeyDown(SDLK_a)) {
		vel = vel + Vector2D(-playerSpeed, 0);
	}
	if (InputHandler::instance()->isKeyDown(SDLK_d)) {
		vel = vel + Vector2D(playerSpeed, 0);
	}
	if (InputHandler::instance()->isKeyDown(SDLK_w)) {
		vel = vel + Vector2D(0, -playerSpeed);
	}
	if (InputHandler::instance()->isKeyDown(SDLK_s)) {
		vel = vel + Vector2D(0, playerSpeed);
	}
	if(vel.magnitude()!=0)
	vel = vel / vel.magnitude();
	vel = vel * playerSpeed;
	transform->setVel(vel);
	
	
}

void PlayerMovementComponent::setPlayerSpeed(int newSpeed) {
	playerSpeed = newSpeed;
}