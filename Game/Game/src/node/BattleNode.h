#pragma once
#ifndef BATTLENODE_H_
#define BATTLENODE_H_

#include "Node.h"
#include "../core/SDLApplication.h"

// cleon says: cuidado con las dependencias cruzadas. recordad los 800 errores de TPV. 800 errores == 800 gatitos menos.
class BattleScene;
class NodeButtonComponent;

enum battleType {
	_PASTBATTLE = 0,
	_PRESENTBATTLE,
	_FUTUREBATTLE
};

class BattleNode : public Node {
	friend Node;
	friend NodeButtonComponent;
private:

	static list<battleType>::iterator* lastType;
	static list<battleType> battleTypes;
	list<battleType>::iterator type;


	//battleType type;
	BattleNode(Vector2D const& pos);
public:
	virtual CallBack* loadNode() const;
	// cleon says: MAAAAAALLLLLLLLLLLLLLLLLLLLL. igual a veces sí que es bueno tener miedo.
	virtual list<battleType>::iterator* getIt() { return &type; }
	// Devuelve la clave de la textura del nodo
	inline virtual string getTextureKey() const { return Node::getTextureKey() + to_string((int)*type); }
};

#endif // !BATTLENODE_H_
