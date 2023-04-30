#include "NodeButtonComponent.h"
#include "../../scenes/GameState.h"

// Constructora que recibe un iterador al tipo de  batalla, un callback y un puntero al estado del nodo
NodeButtonComponent::NodeButtonComponent(CallBack _f, nodeState const& _nState, float navigatorHorizontalMult) :
ButtonComponent(_f, nullptr, -1, false), nState(_nState), horizontalMult(navigatorHorizontalMult) {}


void NodeButtonComponent::initComponent() {
	ButtonComponent::initComponent();
	myData = butNav->insert(animButton, horizontalMult, 0.5f);
}

// Actualiza la animación del botón según el estado
void NodeButtonComponent::updateAnimation() {
	switch (nState) {
	case _LOCKED_NODE:
		changeStateAnim(ONLOCKED, state);
		break;
	case _COMPLETED_NODE:
		changeStateAnim(ONCOMPLETED, state);
		break;
	default:
		ButtonComponent::updateAnimation();
		break;
	}
}

// Ejecuta el callback del botón si este está disponible
void NodeButtonComponent::onClick() {
	if (!(nState == _LOCKED_NODE || nState == _COMPLETED_NODE)) {
		ButtonComponent::onClick();
	}
}