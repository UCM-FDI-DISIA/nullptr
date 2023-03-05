#include "ShopNode.h"
#include "../../core/SDLApplication.h"

// Constructora, recibe posición del nodo en el mapa
ShopNode::ShopNode(Vector2D const& pos) : 
	Node(SHOP_NODE_TEXTURE_KEY, pos,
		[]() {
			SDLApplication::newScene<ShopScene>();
		}) {
}