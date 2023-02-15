#include "ButtonComponent.h"
#include "../core/GameObject.h"

void ButtonComponent::update() {
	int mouseX = 0, mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);

	// Cambia el estado según la posición del ratón
	if ((mouseX >= tr->getPos().getX() && mouseX < tr->getPos().getX() + tr->getWidth()) &&
		(mouseY >= tr->getPos().getY() && mouseY < tr->getPos().getY() + tr->getHeight()))
		state = OnOver;
	else state = OnOut;

	// Cambiar animación según el estado
	switch (state) {
		case 0: changeStateAnim("Idle"); break;
		case 1: changeStateAnim("OnOver"); break;
		case 2: changeStateAnim("OnClick"); break;
	}
}

void ButtonComponent::handleInput() {
	if (InputHandler::instance()->getMouseButtonState(InputHandler::LEFT) && state == OnOver) {
		state = OnClick;
		function(game);
	}
}

void ButtonComponent::initComponent() {
	tr = gObj->getComponent<Transform>();
	animButton = gObj->getComponent<Animator>();
	animFrame = frame->getComponent<Animator>();
}

// Cambia el estado de los animators para mostrar el estado del botón recibido
void ButtonComponent::changeStateAnim(string key) {
	if (animButton->currentAnimationKey() != key) {			// Comprobar si la animación actual no es a la que hay que cambiar
		animButton->play(key);								// Reproducir la correspondiente
		if (frame != nullptr) animFrame->play(key);			// Cambiar el estado del frame al correspondiente
	}
}