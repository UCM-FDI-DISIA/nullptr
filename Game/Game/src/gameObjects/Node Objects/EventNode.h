#pragma once

#include "Node.h"

class EventNode : public Node {
public:
	// Constructora, recibe posición del nodo en el mapa
	EventNode(Vector2D const& pos);
};
