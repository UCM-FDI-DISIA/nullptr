#include "ButtonComponent.h"
#include "../../gameObjects/GameObject.h"
#include "../../scenes/GameState.h"

void ButtonComponent::update() {
	// Cambiar animaci�n seg�n el estado
	updateAnimation();

	int mouseX = 0, mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);

	// Cambia el estado seg�n la posici�n del rat�n
	if (state != OnClick) {
		if (isOver(mouseX, mouseY)) {
			setAsCurrentButton();
			state = OnOver;
		}
		else {
			state = OnOut;
		}
	}
}

void ButtonComponent::handleInput() {
	if (state == OnOver) {
		if (gmCtrl_.click()) {
			onClick();
		}
		// MOVER JOYSTICK
		if (gmCtrl_.selectUpButton()) {
			butNav->up();
		}
		if (gmCtrl_.selectDownButton()) {
			butNav->down();
		}
		if (gmCtrl_.selectLeftButton()) {
			butNav->left();
		}
		if (gmCtrl_.selectRightButton()) {
			butNav->right();
		}
	}
}

void ButtonComponent::initComponent() {
	animButton = gObj->getComponent<Animator>();
	if (frame != nullptr) animFrame = frame->getComponent<Animator>();
	hoverOverSound = &sdlutils().soundEffects().at("HoverOverButton");
	clickSound = &sdlutils().soundEffects().at("ButtonPressed");
	
	butNav = gStt->getButtonNavigator();
	if (addToNavigation_) myData = butNav->insert(animButton);
}


// Comprueba si las coordenadas introducidas est�n sobre el mouse
bool ButtonComponent::isOver(int mouseX, int mouseY) {
	auto r = animButton->getRect();
	return (mouseX >= r.x && mouseX < r.x + r.w) &&
		(mouseY >= r.y && mouseY < r.y + r.h);
}

// Ejecuta el callback
void ButtonComponent::onClick() {
	state = OnClick;
	function();
}


// Actualiza la animaci�n del bot�n seg�n el estado
void ButtonComponent::updateAnimation() {
	switch (state) {
	case OnOut:
		changeStateAnim(ONOUT, state);
		break;
	case OnOver:
		changeStateAnim(ONOVER, state);
		break;
	case OnClick:
		changeStateAnim(ONCLICK, state);
		break;
	}
}

// Cambia el estado de los animators para mostrar el estado del bot�n recibido
void ButtonComponent::changeStateAnim(string key, int state) {
	// Comprobar si la animaci�n actual no es a la que hay que cambiar
	if (animButton->currentAnimationKey() != key) {
		switch (state) {
		case OnClick:
			clickSound->play();
			break;
		case OnOver:
			hoverOverSound->play();
			break;
		}
		// Reproducir la correspondiente
		animButton->play(key);

		// Cambiar el estado del frame al correspondiente
		if (frame != nullptr) animFrame->play(key);
	}
}


void ButtonComponent::setAsCurrentButton() {
	butNav->setCurrentButton(myData);
}