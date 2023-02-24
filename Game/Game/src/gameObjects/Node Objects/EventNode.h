#pragma once
#ifndef EVENTNODE_H_
#define EVENTNODE_H_

#include "Node.h"

class EventNode : public Node {
	friend Node;
private:
	// Constructora, recibe posición del nodo en el mapa
	EventNode(Vector2D const& pos);
public:
	// Devuelve un CallBack que abre la escena de evento
	virtual CallBack loadNode() const;
};

#endif // !EVENTNODE_H_
