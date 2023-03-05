#pragma once

#include "../../gameObjects/GameObject.h"
#include "../../components/Node Components/NodeButtonComponent.h"

class NodeButton : public GameObject {
public:
	// Añade los componentes al botón y crea sus animaciones
	virtual void initGameObject(vector<Node*>::const_iterator nodeIt, CallBack _cb);
};
