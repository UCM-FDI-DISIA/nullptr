#include "Node.h"

#include "BattleNode.h"
#include "ShopNode.h"
#include "ChestNode.h"
#include "EventNode.h"

Node::Node(string tKey) : state(_LOCKED_NODE), nextNodes(), textureKey(tKey) {}

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
void Node::setNextNodes(const vector<Node*>& nNodes) {
	nextNodes = nNodes;
}

// Cambia el estado a completado y desbloquea los siguientes nodos
void Node::complete() {
	state = _COMPLETED_NODE;
	unlockNextNodes();
}

inline const string& Node::getTextureKey() const { return textureKey; }

// Inicializa el mapa completo de Nodos
void Node::initializeNodeMap() {
	nodeMap.push_back(new BattleNode());
	nodeMap.push_back(new ShopNode());
	nodeMap.push_back(new ChestNode());
	nodeMap.push_back(new EventNode());
	nodeMap.push_back(new BattleNode());


	nodeMap[0]->setNextNodes({ nodeMap[1], nodeMap[2] });
	nodeMap[1]->setNextNodes({ nodeMap[3] });
	nodeMap[2]->setNextNodes({ nodeMap[4] });
}


// Devuelve una referencia al mapa completo de Nodos
inline vector<Node*>& Node::getNodeMap() { return nodeMap; }

// Vacía el mapa completo de Nodos
void Node::clearNodeMap() {
	for (Node* node : nodeMap) {
		delete node;
		node = nullptr;
	}
}