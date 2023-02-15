#include "ButtonComponent.h"
#include "../core/GameObject.h"

void ButtonComponent::update() {
	int mouseX = 0, mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);

	if ((mouseX >= tr->getPos().getX() && mouseX < tr->getPos().getX() + tr->getWidth()) &&
		(mouseY >= tr->getPos().getY() && mouseY < tr->getPos().getY() + tr->getHeight()))
		state = OnOver;
	else state = OnOut;

	// Cambiar animación según el estado
	switch (state) {
		case 0: 
			if (anim->currentAnimationKey() != "Idle") { anim->stop(); anim->play("Idle"); }
		break;
		case 1: 
			if (anim->currentAnimationKey() != "OnOver") { anim->stop(); anim->play("OnOver"); }
		break;
		case 2: anim->stop(); anim->play("OnClick"); break;
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