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
		case OnOut: changeStateAnim(ONOUT); break;
		case OnOver: changeStateAnim(ONOVER); break;
		case OnClick: changeStateAnim(ONCLICK); break;
	}
}

void ButtonComponent::handleInput() {
	if (InputHandler::instance()->getMouseButtonState(InputHandler::LEFT) && state == OnOver) {
		state = OnClick;
		function();
	}
}

void ButtonComponent::initComponent() {
	tr = gObj->getComponent<Transform>();
	animButton = gObj->getComponent<Animator>();
	if (frame != nullptr) animFrame = frame->getComponent<Animator>();
}

// Cambia el estado de los animators para mostrar el estado del botón recibido
void ButtonComponent::changeStateAnim(string key) {
	// Comprobar si la animación actual no es a la que hay que cambiar
	if (animButton->currentAnimationKey() != key) {
		// Reproducir la correspondiente
		animButton->play(key);

		// Cambiar el estado del frame al correspondiente
		if (frame != nullptr) animFrame->play(key);
	}
}