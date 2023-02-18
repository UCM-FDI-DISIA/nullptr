#include "Node.h"

#include "BattleNode.h"
#include "ShopNode.h"
#include "ChestNode.h"
#include "EventNode.h"

Node::Node() : state(_LOCKED_NODE), nextNodes() {}

void Node::unlock() {
	if (state == _LOCKED_NODE) {
		state = _UNLOCKED_NODE;
	}
}

void Node::unlockNextNodes() {
	for (Node* node : nextNodes) {
		node->unlock();
	}
}

void Node::setNextNodes(const vector<Node*>& nNodes) {
	nextNodes = nNodes;
}

void Node::complete() {
	state = _COMPLETED_NODE;
	unlockNextNodes();
}


void Node::initializeNodeMap() {
	nodeMap.push_back(new BattleNode());
	nodeMap.push_back(new BattleNode());
	nodeMap.push_back(new BattleNode());
	nodeMap.push_back(new BattleNode());
	nodeMap.push_back(new BattleNode());


	nodeMap[0]->setNextNodes({nodeMap[1], nodeMap[2]});
}