#pragma once
#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <vector>
#include "../../components/ecs.h"
#include "../../data/constants.h"
using namespace std;

enum nodeState {
	_LOCKED_NODE,
	_UNLOCKED_NODE,
	_COMPLETED_NODE
};

class Node {
private:
	nodeState state;
	vector<Node*> nextNodes;
	string textureKey;
	Vector2D position;
	CallBack load;

public:
	// Constructora, recibe la clave de la textura
	Node(string tKey, Vector2D const& pos, CallBack _load);
	// Asigna el estado del nodo a bloqueado
	void lock();
	// Asigna el estado del nodo a desbloqueado
	void unlock();
	// Cambia el estado a completado y desbloquea los siguientes nodos
	void complete(vector<Node*>& unlockedNodes);
	// Desbloquea los siguientes nodos y bloquea los nodos que estuvieran desbloqueados
	void unlockNextNodes(vector<Node*>& unlockedNodes);
	// Asigna los siguientes nodos
	void setNextNodes(vector<Node*> const& nNodes);
	// Añade el nodo recibido a los siguientes nodos
	void addToNextNodes(Node* node);
	// Devuelve un CallBack distinto para cada tipo de nodo
	CallBack loadNode();
	// Devuelve la clave de la textura del nodo
	inline virtual string getTextureKey() const { return textureKey; }
	// Devuelve la posición asignada al nodo
	inline const Vector2D& getPosition() const { return position; }
	// Devuelve un puntero al estado del nodo
	inline const nodeState& getState() const { return state; }
};

#endif // NODE_H_
