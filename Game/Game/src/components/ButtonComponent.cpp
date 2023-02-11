#include "ButtonComponent.h"
#include "../core/GameObject.h"

void ButtonComponent::update() {
	int mouseX = 0, mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);

	if ((mouseX >= tr->getPos().getX() && mouseX < tr->getPos().getX() + tr->getWidth()) &&
		(mouseY >= tr->getPos().getY() && mouseY < tr->getPos().getY() + tr->getHeight()))
		state = OnOver;
	else state = OnOut;
	
}

void ButtonComponent::handleInput() {
	if (InputHandler::instance()->getMouseButtonState(InputHandler::LEFT) && state == OnOver) {
		state = OnClick;
		function(mngr);
	}
}

void ButtonComponent::initComponent() {
	tr = gObj->getComponent<Transform>();
}