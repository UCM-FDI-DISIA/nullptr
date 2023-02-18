#pragma once
#ifndef NODE_H_
#define NODE_H_

#include <vector>
using namespace std;

enum nodeState {
	_LOCKED_NODE = 0,
	_UNLOCKED_NODE,
	_COMPLETED_NODE
};

class Node {
private:
	nodeState state;
	vector<Node*> nextNodes;
	
	static vector<Node*> nodeMap;
	
	// Asigna el estado del nodo a desbloqueado
	void unlock();
	// Desbloquea los siguientes nodos
	void unlockNextNodes();
public:
	Node();
	// Asigna los siguientes nodos
	void setNextNodes(const vector<Node*>& nNodes);
	// Cambia el estado a completado y desbloquea los siguientes nodos
	void complete();
	// Carga el nodo correspondiente
	virtual void loadNode() const = 0;
	// Inicializa el mapa completo de Nodos
	static void initializeNodeMap();
};

#endif // NODE_H_
