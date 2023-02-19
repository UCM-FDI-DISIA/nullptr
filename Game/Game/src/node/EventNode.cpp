#include "EventNode.h"

EventNode::EventNode(Vector2D const& pos) : Node("SalirO", pos) {}

CallBack* EventNode::loadNode() const {
	return MapScene::salir;
}