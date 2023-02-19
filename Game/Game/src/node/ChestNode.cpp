#include "ChestNode.h"

ChestNode::ChestNode(Vector2D const& pos) : Node("Cofre", pos) {}

CallBack* ChestNode::loadNode() const{
	return MapScene::cofre;
}