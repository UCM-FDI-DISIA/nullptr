#pragma once

#include "Node.h"
#include <string>
class BattleScene;

enum battleType {
	_PASTBATTLE,
	_PRESENTBATTLE,
	_FUTUREBATTLE
};

class BattleNode : public Node {
private:
	// Tipo de batalla del nodo, aleatoria para cada instancia
	battleType type;

public:
	// Constructora, recibe posición del nodo en el mapa
	BattleNode(Vector2D const& pos);
	// Devuelve un CallBack que abre la escena de batalla del tipo del nodo
	virtual CallBack loadNode() const;
	// Devuelve la clave de la textura del nodo
	inline virtual string getTextureKey() const { return Node::getTextureKey() + to_string((int)type); }
};
