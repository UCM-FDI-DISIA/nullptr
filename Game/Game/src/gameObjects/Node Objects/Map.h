#pragma once

#include "../../utils/Singleton.h"
#include "BattleNode.h"
#include "ShopNode.h"
#include "ChestNode.h"
#include "EventNode.h"

class Map : public Singleton<Map> {
	friend Singleton<Map>;
private:
	// Mapa de todos los nodos
	vector<Node*> nodeMap;
	vector<Node*> initialNodes;
	vector<Node*>& unlockedNodes;
	Node* currentNode; // Nodo actual

	// Añade un nuevo nodo al mapa
	template<typename T>
	Node* addNode(Vector2D pos) {
		T* n = new T(pos);
		nodeMap.push_back(n);
		return n;
	}
	// Añade un nuevo nodo al mapa y a los nodos iniciales
	template<typename T>
	Node* addToInitialNodes(Vector2D pos) {
		Node* n = addNode<T>(pos);
		n->unlock();
		initialNodes.push_back(n);
		return n;
	}

	// Constructora
	Map();
public:
	// Destructora
	~Map();
	// Asigna el nodo actual
	void setCurrentNode(Node* node);
	// Completa el nodo actual
	void completeCurrentNode();
	// Devuelve una referencia constante al mapa de nodos
	inline vector<Node*> const& getNodeMap() { return nodeMap; }
};
// Referencia a la instancia del mapa
inline Map& map() { return *Map::instance(); }