#include "ButtonComponent.h"
#include "../../gameObjects/GameObject.h"
#include "../../scenes/GameState.h"

void ButtonComponent::update() {
	// Cambiar animación según el estado
	updateAnimation();

	int mouseX = 0, mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);

	if (butNav->isCurrentButton(animButton)) {
		if (state != OnOver && onSelected_ != nullptr) onSelected_(tr_);
		auto r = animButton->getRect();
		gmCtrl_.moveMouse(r.x + r.w / 2, r.y + r.h / 2);
	}

	// Cambia el estado según la posición del ratón
	if (isOver(mouseX, mouseY)) {
		state = OnOver;
	}
	else {
		state = OnOut;
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
	tr_ = gObj->getComponent<Transform>();
}


// Comprueba si las coordenadas introducidas están sobre el mouse
bool ButtonComponent::isOver(int mouseX, int mouseY) {
	auto r = animButton->getRect();
	return (mouseX >= r.x && mouseX < r.x + r.w) &&
		(mouseY >= r.y && mouseY < r.y + r.h);
}

// Ejecuta el callback
void ButtonComponent::onClick() {
	gStt->setLastIndex(index);
	state = OnClick;
	function();
}


// Actualiza la animación del botón según el estado
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

// Cambia el estado de los animators para mostrar el estado del botón recibido
void ButtonComponent::changeStateAnim(string key, int state) {
	// Comprobar si la animación actual no es a la que hay que cambiar
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

void ButtonComponent::setOnSelected(std::function<void(Transform*)> onSel) {
	onSelected_ = onSel;
}