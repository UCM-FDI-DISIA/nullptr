#pragma once
#ifndef NODEBUTTONCOMPONENT_H_
#define NODEBUTTONCOMPONENT_H_

#include "ButtonComponent.h"
#include "../node/BattleNode.h"

class NodeButtonComponent : public ButtonComponent {
private:
	// Estados representados por n?meros
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
	NodeButtonComponent(list<battleType>::iterator* _it, CallBack* _f, nodeState const* _nState);
	
	// Actualiza el estado del bot?n
	virtual void update();

	// Actualiza la animaci?n del bot?n seg?n el estado
	virtual void updateAnimation();

	// Ejecuta el callback del bot?n si este est? disponible
	virtual void onClick();
};

#endif // !NODEBUTTONCOMPONENT_H_
