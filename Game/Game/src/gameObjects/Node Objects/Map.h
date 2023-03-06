#pragma once

#include "../../utils/Singleton.h"
#include "BattleNode.h"
#include "ShopNode.h"
#include "ChestNode.h"
#include "EventNode.h"
#include <unordered_map>

class Map : public Singleton<Map> {
	friend Singleton<Map>;
private:
	// Mapa de todos los nodos
	unordered_map<string, Node*> nodeMap;
	vector<Node*> initialNodes;
	vector<Node*>& unlockedNodes;
	Node* currentNode; // Nodo actual

	// Añade un nuevo nodo al mapa
	template<typename T>
	Node* addNode(string name, Vector2D pos) {
		T* n = new T(pos);
		nodeMap[name] = n;
		return n;
	}
	// Añade un nuevo nodo al mapa y a los nodos iniciales
	template<typename T>
	Node* addToInitialNodes(string name, Vector2D pos) {
		Node*& n = addNode<T>(name, pos);
		n->unlock();
		initialNodes.push_back(n);
		return n;
	}

	inline Node* addNode(string type, string name, Vector2D pos) {
		if (type == "battle") return addNode<BattleNode>(name, pos);
		else if (type == "shop") return addNode<ShopNode>(name, pos);
		else if (type == "chest") return addNode<ChestNode>(name, pos);
		else if (type == "event") return addNode<EventNode>(name, pos);
	}

	// Constructora
	Map();
public:
	// Destructora
	~Map();
	// Inicializa el mapa de nodos
	void initMap(string filename);
	// Asigna el nodo actual
	void setCurrentNode(Node* node);
	// Completa el nodo actual
	void completeCurrentNode();
	// Devuelve una referencia constante al mapa de nodos
	inline unordered_map<string, Node*> const& getNodeMap() { return nodeMap; }
};
// Referencia a la instancia del mapa
inline Map& map() { return *Map::instance(); }