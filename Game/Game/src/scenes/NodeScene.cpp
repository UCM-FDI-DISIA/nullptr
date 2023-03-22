#include "NodeScene.h"
#include "../gameObjects/Node Objects/Map.h"

NodeScene::~NodeScene() {
	map().completeCurrentNode();
}