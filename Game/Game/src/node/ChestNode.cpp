#include "ChestNode.h"
#include "../core/SDLApplication.h"

// Constructora, recibe posición del nodo en el mapa
ChestNode::ChestNode(Vector2D const& pos) : Node(CHEST_NODE_TEXTURE_KEY, pos) {}

// Devuelve un CallBack que abre la escena de cofre
CallBack ChestNode::loadNode() const{
	return []() {
		SDLApplication::newScene<ChestScene>();
	};
}