#include "EventNode.h"

EventNode::EventNode(Vector2D const& pos) : Node(EVENT_NODE_TEXTURE_KEY, pos) {}

CallBack* EventNode::loadNode() const {
	return MapScene::exit;
}