#include "Node.h"

#include "BattleNode.h"
#include "ShopNode.h"
#include "ChestNode.h"
#include "EventNode.h"

vector<Node*> Node::nodeMap = vector<Node*>();

// Constructora, recibe la clave de la textura
Node::Node(string tKey) : state(_LOCKED_NODE), nextNodes(), textureKey(tKey) {
	nodeMap.push_back(this);
}

// Asigna el estado del nodo a desbloqueado
void Node::unlock() {
	if (state == _LOCKED_NODE) {
		state = _UNLOCKED_NODE;
	}
}

// Desbloquea los siguientes nodos
void Node::unlockNextNodes() {
	for (Node* node : nextNodes) {
		node->unlock();
	}
}

// Asigna los siguientes nodos
void Node::setNextNodes(vector<Node*> const& nNodes) {
	nextNodes = nNodes;
}

// Cambia el estado a completado y desbloquea los siguientes nodos
void Node::complete() {
	state = _COMPLETED_NODE;
	unlockNextNodes();
}


// MÉTODOS ESTÁTICOS

// Inicializa el mapa completo de Nodos
void Node::initializeNodeMap() {
	new BattleNode();
	new ShopNode();
	new ChestNode();
	new EventNode();
	new BattleNode();

	nodeMap[0]->setNextNodes({ nodeMap[1], nodeMap[2] });
	nodeMap[1]->setNextNodes({ nodeMap[3] });
	nodeMap[2]->setNextNodes({ nodeMap[4] });
}

// Vacía el mapa completo de Nodos
void Node::clearNodeMap() {
	for (Node* node : nodeMap) {
		delete node;
		node = nullptr;
	}
}