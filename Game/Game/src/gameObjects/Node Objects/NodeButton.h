#pragma once
#ifndef NODEBUTTON_H_
#define NODEBUTTON_H_

#include "../../components/Node Components/NodeButtonComponent.h"

class NodeButton : public GameObject {
public:
	// Añade los componentes al botón y crea sus animaciones
	virtual void initGameObject(vector<Node*>::const_iterator nodeIt, CallBack _cb);
};

#endif // !NODEBUTTON_H_