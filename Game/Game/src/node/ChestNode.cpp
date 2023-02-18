#include "ChestNode.h"

ChestNode::ChestNode() : Node("Cofre") {}

CallBack* ChestNode::loadNode() const{
	return MapScene::cofre;
}