#include "ShopNode.h"

ShopNode::ShopNode() : Node() {}

void ShopNode::loadNode() const {
	SDLApplication::newScene<ShopScene>();
}