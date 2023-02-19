#include "ShopNode.h"

ShopNode::ShopNode(Vector2D const& pos) : Node("Tienda", pos) {}

CallBack* ShopNode::loadNode() const {
	return MapScene::tienda;
}