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
	Node* currentNode;

	template<typename T>
	Node* addNode(Vector2D pos) {
		T* n = new T(pos);
		nodeMap.push_back(n);
		return n;
	}
	template<typename T>
	Node* addToInitialNodes(Vector2D pos) {
		Node* n = addNode<T>(pos);
		n->unlock();
		initialNodes.push_back(n);
		return n;
	}
	Map();
public:
	~Map();
	void completeCurrentNode();
	inline vector<Node*> const& getNodeMap() { return nodeMap; }
};

inline Map& map() { return *Map::instance(); }