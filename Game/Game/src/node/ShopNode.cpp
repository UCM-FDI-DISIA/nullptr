#include "ShopNode.h"

ShopNode::ShopNode() : Node("Tienda") {}

CallBack* ShopNode::loadNode() const {
	return MapScene::tienda;
}