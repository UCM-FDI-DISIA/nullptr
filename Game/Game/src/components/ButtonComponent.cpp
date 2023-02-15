#include "ButtonComponent.h"
#include "../core/GameObject.h"

void ButtonComponent::update() {
	int mouseX = 0, mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);

	if ((mouseX >= tr->getPos().getX() && mouseX < tr->getPos().getX() + tr->getWidth()) &&
		(mouseY >= tr->getPos().getY() && mouseY < tr->getPos().getY() + tr->getHeight())) {
		if (anim->currentAnimationKey() != "OnOver") anim->stop();
		state = OnOver;
		anim->play("OnOver");
	}
	else {
		if (anim->currentAnimationKey() != "Idle") anim->stop();
		state = OnOut;
		anim->play("Idle");
	}
}

void ButtonComponent::handleInput() {
	if (InputHandler::instance()->getMouseButtonState(InputHandler::LEFT) && state == OnOver) {
		anim->stop();
		state = OnClick;
		function(game);
	}
}

void ButtonComponent::initComponent() {
	tr = gObj->getComponent<Transform>();
	anim = gObj->getComponent<Animator>();
}