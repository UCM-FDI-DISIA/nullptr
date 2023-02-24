#include "NodeButtonComponent.h"

// Constructora que recibe un iterador al tipo de  batalla, un callback y un puntero al estado del nodo
NodeButtonComponent::NodeButtonComponent(CallBack _f, nodeState const& _nState) :
ButtonComponent(_f, nullptr), nState(_nState) {}

// Actualiza el estado del botón
void NodeButtonComponent::update() {
	ButtonComponent::update();
	if (nState == _LOCKED_NODE) state = OnLocked;
	else if (nState == _COMPLETED_NODE) state = OnCompleted;
}

// Actualiza la animación del botón según el estado
void NodeButtonComponent::updateAnimation() {
	if (state == OnLocked) {
		changeStateAnim(ONLOCKED);
	}
	else if (state == OnCompleted) {
		changeStateAnim(ONCOMPLETED);
	}
	else ButtonComponent::updateAnimation();
}

// Ejecuta el callback del botón si este está disponible
void NodeButtonComponent::onClick() {
	if (!(state == OnLocked || state == OnCompleted)) {
		ButtonComponent::onClick();
	}
}