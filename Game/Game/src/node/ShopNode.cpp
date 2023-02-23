#include "ShopNode.h"
#include "../core/SDLApplication.h"

ShopNode::ShopNode(Vector2D const& pos) : Node(SHOP_NODE_TEXTURE_KEY, pos) {}

CallBack ShopNode::loadNode() const {
	return []() {
		SDLApplication::newScene<ShopScene>();
	};
}