#include "EventNode.h"

EventNode::EventNode() : Node("Salir0") {}

CallBack* EventNode::loadNode() const {
	return MapScene::salir;
}