#include "ChestNode.h"

ChestNode::ChestNode() : Node() {}

void ChestNode::loadNode() const{
	SDLApplication::newScene<ChestScene>();
}