#pragma once
#ifndef NODEBUTTONCOMPONENT_H_
#define NODEBUTTONCOMPONENT_H_

#include "ButtonComponent.h"
#include "../node/BattleNode.h"

class NodeButtonComponent : public ButtonComponent {
private:
	// Estados representados por números
	enum State {
		OnOut = 0,
		OnOver,
		OnClick, 
		OnLocked,
		OnCompleted };

	list<battleType>::iterator* it;
	nodeState const* nState;
public:
	// Constructora que recibe un iterador al tipo de  batalla, un callback y un puntero al estado del nodo
	NodeButtonComponent(list<battleType>::iterator* _it, CallBack* _f, nodeState const* _nState) :
	ButtonComponent(_f, nullptr), it(_it), nState(_nState) {}
	
	// Actualiza el estado del botón
	virtual void update() {
		ButtonComponent::update();
		if (*nState == _LOCKED_NODE) state = OnLocked;
		else if (*nState == _COMPLETED_NODE) state = OnCompleted;
	}

	// Actualiza la animación del botón según el estado
	virtual void updateAnimation() {
		if (state == OnLocked) {
			changeStateAnim(ONLOCKED);
		}
		else if (state == OnCompleted) {
			changeStateAnim(ONCOMPLETED);
		}
		else ButtonComponent::updateAnimation();
	}

	// Ejecuta el callback del botón si este está disponible
	virtual void onClick() {
		if (!(state == OnLocked || state == OnCompleted)) {
			BattleNode::lastType = it;
			ButtonComponent::onClick();
		}
	}
};

#endif // !NODEBUTTONCOMPONENT_H_
