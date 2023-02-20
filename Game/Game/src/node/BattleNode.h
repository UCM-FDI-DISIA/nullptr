#pragma once
#ifndef BATTLENODE_H_
#define BATTLENODE_H_

#include "Node.h"
#include "../core/SDLApplication.h"
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
	virtual list<battleType>::iterator* getIt() { return &type; }
	// Devuelve la clave de la textura del nodo
	inline virtual const string& getTextureKey() const { return Node::getTextureKey() + to_string((int)*type); }
};

#endif // !BATTLENODE_H_
