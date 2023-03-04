#include "Map.h"

Map::Map() : nodeMap(vector<Node*>()), initialNodes(vector<Node*>()), unlockedNodes(initialNodes), currentNode(nullptr) {
	// Crear el mapa de nodos
	// Crear los nodos (con unos iniciales desbloqueados)
	
	// inicializar el vector con los niveles iniciales
	addToInitialNodes<BattleNode>({ NODE_LEVEL_X[0], NODE_LEVEL_Y[0] });
	addToInitialNodes<ChestNode>({ NODE_LEVEL_X[1], NODE_LEVEL_Y[0] });
	addToInitialNodes<BattleNode>({ NODE_LEVEL_X[2], NODE_LEVEL_Y[0] });
	addToInitialNodes<BattleNode>({ NODE_LEVEL_X[0], NODE_LEVEL_Y[1] });
	addToInitialNodes<ShopNode>({ NODE_LEVEL_X[1], NODE_LEVEL_Y[1] });
	addToInitialNodes<EventNode>({ NODE_LEVEL_X[2], NODE_LEVEL_Y[1] });

	// asignar los nodos que se desbloquean al completar cada nodo
	nodeMap[0]->setNextNodes({ nodeMap[3], nodeMap[4] });
	nodeMap[1]->addToNextNodes(nodeMap[3]);
	nodeMap[2]->setNextNodes({ nodeMap[4] });
}

Map::~Map() {
	// Borrar el mapa de nodos
	for (Node*& node : nodeMap) {
		delete node;
		node = nullptr;
	}
}

void Map::completeCurrentNode() {
	currentNode->complete(unlockedNodes);
}