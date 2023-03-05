#include "EventNode.h"
#include "../../core/SDLApplication.h"

// Constructora, recibe posición del nodo en el mapa
EventNode::EventNode(Vector2D const& pos) : 
	Node(EVENT_NODE_TEXTURE_KEY, pos,
		[]() {
			SDLApplication::newScene<MainMenuScene>();
		}) {
}