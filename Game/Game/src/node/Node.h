#pragma once
#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <vector>
#include "../scenes/MapScene.h"
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
	string textureKey;

	static vector<Node*> nodeMap;
	
	// Asigna el estado del nodo a desbloqueado
	void unlock();
	// Desbloquea los siguientes nodos
	void unlockNextNodes();
public:
	Node(string tKey);
	// Asigna los siguientes nodos
	void setNextNodes(const vector<Node*>& nNodes);
	// Cambia el estado a completado y desbloquea los siguientes nodos
	void complete();
	// Carga el nodo correspondiente
	virtual CallBack* loadNode() const = 0;
	// Devuelve la clave de la textura del nodo
	inline const string& getTextureKey() const;
	// Inicializa el mapa completo de Nodos
	static void initializeNodeMap();
	// Devuelve una referencia al mapa completo de Nodos
	static inline vector<Node*>& getNodeMap();
	// Vacía el mapa completo de Nodos
	static void clearNodeMap();

};

#endif // NODE_H_
