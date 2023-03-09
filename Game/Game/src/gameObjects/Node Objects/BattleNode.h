#pragma once
#ifndef BATTLENODE_H_
#define BATTLENODE_H_

#include "Node.h"
#include "../../core/SDLApplication.h"

// cleon says: cuidado con las dependencias cruzadas. recordad los 800 errores de TPV. 800 errores == 800 gatitos menos.
class BattleScene;
class NodeButtonComponent;

enum battleType {
	_PASTBATTLE,
	_PRESENTBATTLE,
	_FUTUREBATTLE,
	_BOSSBATTLE
};

class BattleNode : public Node {
	friend Node;
private:
	// Tipo de batalla del nodo, aleatoria para cada instancia
	battleType type;

	// Constructora, recibe posición del nodo en el mapa
	BattleNode(Vector2D const& pos);
public:
	// Devuelve un CallBack que abre la escena de batalla del tipo del nodo
	virtual CallBack loadNode() const;
	// Devuelve la clave de la textura del nodo
	inline virtual string getTextureKey() const { return Node::getTextureKey() + to_string((int)type); }
};

#endif // !BATTLENODE_H_
