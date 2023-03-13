#include "Node.h"

#include "Map.h"

// Constructora, recibe la clave de la textura
Node::Node(Needs n, string tKey, CallBack _load, NodeType t, BattleType bt) : 
	needed(n), textureKey(tKey), load(_load), state(_LOCKED_NODE), type(t), bType(bt) {}

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

// Cambia el estado a completado y cambia los nodos desbloqueados
void Node::complete(vector<Node*>& unlockedNodes) {
	state = _COMPLETED_NODE;
	unlockNextNodes(unlockedNodes);
}

// Desbloquea los siguientes nodos y bloquea los nodos que estuvieran desbloqueados
void Node::unlockNextNodes(vector<Node*>& unlockedNodes) {
	for (Node* node : unlockedNodes) {
		node->lock();
	}

	unlockedNodes = nextNodes;
	for (Node* node : nextNodes) {
		node->unlock();
	}
}

// Añade el nodo recibido a los siguientes nodos
void Node::addToNextNodes(Node* node, int ind) {
	nextNodes.push_back(node);
	nextInd.push_back(ind);
	++contNext;

	// Hay una cierta probabilidad de que ese enlace cuente como doble (si es así no se podrá enlazar a ningún nodo más)
	if (contNext < 2 && sdlutils().rand().nextInt(0, 20) < 3) contNext++;
}

CallBack Node::loadNode() {
	return [&](){
		map().setCurrentNode(this);
		load();
	};
}


// Comprueba si el nodo conecta con el indice introducido
bool Node::conectsWith(int ind) {
	for (int i = 0; i < nextInd.size(); ++i) {
		if (nextInd[i] == ind) return true;
	}
	return false;
}

// Por si hace falta generar la altura de nuevo
// Elimina todos los enlaces con nodos siguientes
void Node::clearLinks() {
	nextNodes.clear();
	nextInd.clear();
	contNext = 0;
}