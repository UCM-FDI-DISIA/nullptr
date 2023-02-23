#include "EventNode.h"
#include "../core/SDLApplication.h"

EventNode::EventNode(Vector2D const& pos) : Node(EVENT_NODE_TEXTURE_KEY, pos) {}

CallBack EventNode::loadNode() const {
	return []() {
		SDLApplication::newScene<MainMenuScene>();
	};
}