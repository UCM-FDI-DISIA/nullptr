#pragma once
#ifndef NODEBUTTON_H_
#define NODEBUTTON_H_

#include "UI/Button.h"
#include "../components/NodeButtonComponent.h"

class NodeButton : public Button {
public:

	// Añade los componentes al botón y crea sus animaciones
	virtual void initGameObject(list<battleType>::iterator* it, CallBack* _cb, SDLApplication* game, Vector2D _pos, string key, int _w, int _h, int _fw, int _fh, int _r, int _c, GameObject* _frame = nullptr) {
		Button::initGameObject(_cb, game, _pos, key, _w, _h, _fw, _fh, _r, _c, _frame);
		removeComponent<ButtonComponent>();
		addComponent<NodeButtonComponent>(it, _cb, game, _frame);
	}
};

#endif // !NODEBUTTON_H_