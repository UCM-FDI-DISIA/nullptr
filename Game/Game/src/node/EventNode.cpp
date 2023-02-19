#include "EventNode.h"

EventNode::EventNode() : Node("SalirO") {}

CallBack* EventNode::loadNode() const {
	return MapScene::salir;
}