#pragma once
#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <vector>
#include "../components/ecs.h"
#include "../data/constants.h"
using namespace std;

enum battleType;

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

	static vector<Node*> nodeMap;
	static vector<Node*> initialNodes;
	static vector<Node*>& unlockedNodes; // cleon says: hay demasiadas cosas extrañas aquí como para comentarlo.
	
	// Asigna el estado del nodo a bloqueado
	void lock();
	// Asigna el estado del nodo a desbloqueado
	void unlock();
	// Desbloquea los siguientes nodos y bloquea los nodos que estuvieran desbloqueados
	void unlockNextNodes();
protected:
	// Constructora, recibe la clave de la textura
	Node(string tKey, Vector2D const& pos);
public:
	// Asigna los siguientes nodos
	void setNextNodes(vector<Node*> const& nNodes);
	// Añade el nodo recibido a los siguientes nodos
	void addToNextNodes(Node* const& node);
	// Cambia el estado a completado y desbloquea los siguientes nodos
	void complete();
	// Carga el nodo correspondiente
	virtual CallBack loadNode() const = 0;
	// Devuelve la clave de la textura del nodo
	inline virtual string getTextureKey() const { return textureKey; }
	// Devuelve la posición asignada al nodo
	inline const Vector2D& getPosition() const { return position; }
	// Devuelve un puntero al estado del nodo
	inline const nodeState& getState() const { return state; }

	// MÉTODOS ESTÁTICOS
	// Inicializa el mapa completo de Nodos
	static void initializeNodeMap();
	// Devuelve una referencia al mapa completo de Nodos
	static inline const vector<Node*> const& getNodeMap() { return nodeMap; }
	// Vacía el mapa completo de Nodos
	static void clearNodeMap();
};

#endif // NODE_H_
