#pragma once

#include "../../gameObjects/GameObject.h"
#include "../../components/Node Components/NodeButtonComponent.h"

class NodeButton : public GameObject {
public:
	// Añade los componentes al botón y crea sus animaciones
	virtual void initGameObject(Node* nodeIt, CallBack _cb, Vector2D pos, float navigatorhorizontalMult, std::function<void(Transform*)> onSel);


};
