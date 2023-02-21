#include "Node.h"

#include "BattleNode.h"
#include "ShopNode.h"
#include "ChestNode.h"
#include "EventNode.h"

vector<Node*> Node::nodeMap = vector<Node*>();
vector<Node*>* Node::unlockedNodes = nullptr;
vector<Node*> Node::initialNodes = vector<Node*>();

// Constructora, recibe la clave de la textura
Node::Node(string tKey, Vector2D const& pos) : state(_LOCKED_NODE), nextNodes(), textureKey(tKey), position(pos) {
	nodeMap.push_back(this);
}

// Asigna el estado del nodo a bloqueado
void Node::lock() {
	if (state != _COMPLETED_NODE) {
		state = _LOCKED_NODE;
	}
}

// Asigna el estado del nodo a desbloqueado
void Node::unlock() {
	if (state == _LOCKED_NODE) {
		state = _UNLOCKED_NODE;
	}
}

// Desbloquea los siguientes nodos y bloquea los nodos que estuvieran desbloqueados
void Node::unlockNextNodes() {
	for (Node* node : *unlockedNodes) {
		node->lock();
	}

	unlockedNodes = &nextNodes;
	for (Node* node : nextNodes) {
		node->unlock();
	}
}

// Asigna los siguientes nodos
void Node::setNextNodes(vector<Node*> const& nNodes) {
	nextNodes = nNodes;
}

// Añade el nodo recibido a los siguientes nodos
void Node::addToNextNodes(Node* const& node) {
	nextNodes.push_back(node);
}

// Cambia el estado a completado y desbloquea los siguientes nodos
void Node::complete() {
	state = _COMPLETED_NODE;
	unlockNextNodes();
}


// MÉTODOS ESTÁTICOS

// Inicializa el mapa completo de Nodos
void Node::initializeNodeMap() {
	// crear vector con los niveles iniciales y asignarlos al puntero de desbloqueados
	unlockedNodes = &initialNodes;

	// Crear los nodos (con unos iniciales desbloqueados)
	(new BattleNode({NODE_LEVEL_X[0], NODE_LEVEL_Y[0]}))->unlock();
	(new BattleNode({ NODE_LEVEL_X[1], NODE_LEVEL_Y[0] }))->unlock();
	(new ChestNode({ NODE_LEVEL_X[2], NODE_LEVEL_Y[0] }))->unlock();
	(new EventNode({ NODE_LEVEL_X[0], NODE_LEVEL_Y[1] }))->unlock();
	(new ShopNode({ NODE_LEVEL_X[1], NODE_LEVEL_Y[1] }))->unlock();

	// inicializar el vector con los niveles iniciales
	initialNodes = { nodeMap[0], nodeMap[1], nodeMap[2], nodeMap[3], nodeMap[4]};

	// asignar los nodos que se desbloquean al completar cada nodo
	nodeMap[0]->setNextNodes({ nodeMap[3], nodeMap[4] });
	nodeMap[1]->addToNextNodes(nodeMap[3]);
	nodeMap[2]->setNextNodes({ nodeMap[4] });
}

// Vacía el mapa completo de Nodos
void Node::clearNodeMap() {
	for (Node* node : nodeMap) {
		delete node;
		node = nullptr;
	}
}