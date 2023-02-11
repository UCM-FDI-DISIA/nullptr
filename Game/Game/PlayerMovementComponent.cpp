#include "PlayerMovementComponent.h"
#include "../Game/src/sdlutils/InputHandler.h"

PlayerMovementComponent::PlayerMovementComponent() :transform(nullptr){}

void PlayerMovementComponent::initComponent() {
	transform = gObj->getComponent<Transform>();
}

void PlayerMovementComponent::handleInput() {
	if (InputHandler::instance()->isKeyDown(SDLK_a)) {
		transform->setVel(Vector2D(1, 0));
	}
}