#include "ChestNode.h"
#include "../../core/SDLApplication.h"

// Constructora, recibe posici�n del nodo en el mapa
ChestNode::ChestNode(Vector2D const& pos) : 
	Node(CHEST_NODE_TEXTURE_KEY, pos,
		[]() {
			SDLApplication::newScene<ChestScene>();
		}) {
}