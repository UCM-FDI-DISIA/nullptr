#include "ButtonComponent.h"

void ButtonComponent::update() {
	int mouseX = 0, mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);

	if ((mouseX >= transform->getPos().getX() && mouseX < transform->getPos().getX() + transform->getWidth()) &&
		(mouseY >= transform->getPos().getY() && mouseY < transform->getPos().getY() + transform->getHeight()))
		state = OnOver;
	else state = OnOut;
}

void ButtonComponent::handleInput() {
	if (InputHandler::instance()->getMouseButtonState(InputHandler::LEFT) && state == OnOver) {
		state = OnClick;
		//function();
	}
}