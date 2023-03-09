#pragma once
#ifndef CHESTNODE_H_
#define CHESTNODE_H_

#include "Node.h"
class ChestScene;

class ChestNode : public Node {
	friend Node;
private:
	// Constructora, recibe posición del nodo en el mapa
	ChestNode(Vector2D const& pos);
public:
	// Devuelve un CallBack que abre la escena de cofre
	virtual CallBack loadNode() const;
};

#endif // !CHESTNODE_H_
