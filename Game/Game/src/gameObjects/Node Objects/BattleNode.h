#pragma once

#include "Node.h"
#include <string>

enum battleType {
	_PASTBATTLE,
	_PRESENTBATTLE,
	_FUTUREBATTLE,
	_BOSSBATTLE
};

class BattleNode : public Node {
private:
	// Tipo de batalla del nodo, aleatoria para cada instancia
	battleType type;

public:
	// Constructora, recibe posición del nodo en el mapa
	BattleNode(Vector2D const& pos, battleType _t = battleType(sdlutils().rand().nextInt(0, 3)));
	// Devuelve la clave de la textura del nodo
	inline virtual string getTextureKey() const { return Node::getTextureKey() + to_string((int)type); }
};
