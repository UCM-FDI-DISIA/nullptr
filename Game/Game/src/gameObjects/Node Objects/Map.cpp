#include "Map.h"

Map::Map() : nodeMap(vector<Node*>()), initialNodes(vector<Node*>()), unlockedNodes(initialNodes), currentNode(nullptr) {
	// Crear el mapa de nodos
	// Crear los nodos (con unos iniciales desbloqueados)
	
	// Niveles iniciales por defecto
	// k = 0, 0
	addToInitialNodes<BattleNode>(NODE_POSITIONS[0]); // lvl 1 (tutorial)
	// k = 1, 1
	addNode<ChestNode>(NODE_POSITIONS[1]); // primer cofre
	// k = 2, 2, 3
	addNode<BattleNode>(NODE_POSITIONS[2]); // lvl 2 a
	addNode<BattleNode>(NODE_POSITIONS[3]); // lvl 2 b
	// k = 3, 4
	addNode<ShopNode>(NODE_POSITIONS[4]); // primera tienda
	// k = 4, 5
	addNode<ShopNode>(NODE_POSITIONS[5]); // ¿primer evento¿

	// k = 5, 6, 7
	addNode<BattleNode>(NODE_POSITIONS[6]); // lvl 3 a
	addNode<BattleNode>(NODE_POSITIONS[7]); // lvl 3 b
	// k = 6, 8
	addNode<BattleNode>(NODE_POSITIONS[8]); // lvl 4
	// k = 7, 9
	addNode<BattleNode>(NODE_POSITIONS[9]); // lvl 5
	// k = 8, 10, 11
	addNode<ShopNode>(NODE_POSITIONS[10]);
	addNode<ChestNode>(NODE_POSITIONS[11]);

	// k = 8, 12
	addNode<BattleNode>(NODE_POSITIONS[12]); // lvl 6
	// k = 9, 13
	addNode<BattleNode>(NODE_POSITIONS[13]); // lvl 7
	// k = 10, 14, 15
	addNode<BattleNode>(NODE_POSITIONS[14]); // lvl 8 a
	addNode<BattleNode>(NODE_POSITIONS[15]); // lvl 8 b
	
	// k = 11, 16, 17
	addNode<ShopNode>(NODE_POSITIONS[16]);
	addNode<ChestNode>(NODE_POSITIONS[17]);

	// k = 12, 18
	addNode<BattleNode>(NODE_POSITIONS[18]); // lvl 9
	// k = 13, 19
	addNode<BattleNode>(NODE_POSITIONS[19]); // lvl 10

	// k = n - 1, 20
	addNode<ChestNode>(NODE_POSITIONS[20]); // cofre antes del jefe
	// k = n, 21
	addNode<BattleNode>(NODE_POSITIONS[21]); // boss final

	// asignar los nodos que se desbloquean al completar cada nodo
	nodeMap[0]->addToNextNodes(nodeMap[1]);

	nodeMap[1]->addToNextNodes(nodeMap[2]);
	nodeMap[1]->addToNextNodes(nodeMap[3]);
	
	nodeMap[2]->addToNextNodes(nodeMap[4]);
	
	nodeMap[3]->addToNextNodes(nodeMap[4]);
	
	nodeMap[4]->addToNextNodes(nodeMap[5]);

	nodeMap[5]->addToNextNodes(nodeMap[6]);
	nodeMap[5]->addToNextNodes(nodeMap[7]);

	nodeMap[6]->addToNextNodes(nodeMap[8]);
	nodeMap[7]->addToNextNodes(nodeMap[8]);

	nodeMap[8]->addToNextNodes(nodeMap[9]);

	nodeMap[9]->addToNextNodes(nodeMap[10]);
	nodeMap[9]->addToNextNodes(nodeMap[11]);

	nodeMap[10]->addToNextNodes(nodeMap[12]);
	nodeMap[11]->addToNextNodes(nodeMap[12]);

	nodeMap[12]->addToNextNodes(nodeMap[13]);

	nodeMap[13]->addToNextNodes(nodeMap[14]);
	nodeMap[13]->addToNextNodes(nodeMap[15]);

	nodeMap[14]->addToNextNodes(nodeMap[16]);

	nodeMap[15]->addToNextNodes(nodeMap[17]);

	nodeMap[16]->addToNextNodes(nodeMap[18]);
	nodeMap[17]->addToNextNodes(nodeMap[18]);

	nodeMap[18]->addToNextNodes(nodeMap[19]);
	nodeMap[19]->addToNextNodes(nodeMap[20]);
	nodeMap[20]->addToNextNodes(nodeMap[21]);


}

Map::~Map() {
	// Borrar el mapa de nodos
	for (Node*& node : nodeMap) {
		delete node;
		node = nullptr;
	}
}

void Map::setCurrentNode(Node* node) {
	currentNode = node;
}

void Map::completeCurrentNode() {
	currentNode->complete(unlockedNodes);
}