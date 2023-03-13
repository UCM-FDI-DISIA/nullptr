#pragma once
#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <vector>
#include "../../components/ecs.h"
#include "../../data/constants.h"
#include "../../sdlutils/SDLUtils.h"
using namespace std;


enum NodeType {
	Battle,
	Chest,
	Shop,
	None
};

enum BattleType {
	_PASTBATTLE,
	_PRESENTBATTLE,
	_FUTUREBATTLE,
	_NONE,
	_BOSSBATTLE
};

enum nodeState {
	_LOCKED_NODE,
	_UNLOCKED_NODE,
	_COMPLETED_NODE
};

struct Needs {
	NodeType type;
	int battleCounter;
	bool battleOnNext;

	Needs() : type(None), battleCounter(0), battleOnNext(false) {}
	Needs(NodeType t, int bc, bool bon) : type(t), battleCounter(bc), battleOnNext(bon) {}
};

class Node {
private:
	nodeState state;
	string textureKey;
	CallBack load;

	vector<Node*> nextNodes;
	vector<int> nextInd;
	int contNext;

	NodeType type;
	BattleType bType;
	Needs needed;
public:
	// Constructora, recibe la clave de la textura
	Node(Needs n, string tKey, CallBack _load, NodeType t, BattleType bt = BattleType::_NONE);
	// Asigna el estado del nodo a bloqueado
	void lock();
	// Asigna el estado del nodo a desbloqueado
	void unlock();
	// Cambia el estado a completado y desbloquea los siguientes nodos
	void complete(vector<Node*>& unlockedNodes);
	// Desbloquea los siguientes nodos y bloquea los nodos que estuvieran desbloqueados
	void unlockNextNodes(vector<Node*>& unlockedNodes);
	// Añade el nodo recibido a los siguientes nodos
	void addToNextNodes(Node* node, int ind);
	// Devuelve un CallBack distinto para cada tipo de nodo
	CallBack loadNode();
	// Devuelve la clave de la textura del nodo
	inline virtual string getTextureKey() const { 
		if (type != Battle) return textureKey;
		return textureKey + to_string((int)bType);
	}
	// Devuelve un puntero al estado del nodo
	inline const nodeState& getState() const { return state; }

	// Devuelve el tipo de nodo
	inline NodeType getType() { return type; }
	// Devuelve el tipo de batalla del nodo
	inline BattleType getBattleType() { return bType; }
	// Devuelve las necesidades del nodo para haberse creado
	inline Needs getNeeded() { return needed; }
	// Devuelve el número de nodos siguientes
	inline int getNextCount() { return contNext; }
	// Comprueba si el nodo conecta con el indice introducido
	bool conectsWith(int ind);
	// Por si hace falta generar la altura de nuevo
	// Elimina todos los enlaces con nodos siguientes
	void clearLinks();
};

#endif // NODE_H_
