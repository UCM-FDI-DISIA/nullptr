#include "EventNode.h"

EventNode::EventNode() : Node() {}

void EventNode::loadNode() const {
	SDLApplication::instance()->newScene<EventScene>();
}