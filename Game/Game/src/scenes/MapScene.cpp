#include "MapScene.h"
#include "../core/SDLApplication.h"
#include "../gameObjects/Node Objects/NodeButton.h"

MapScene::MapScene() {
	unordered_map<string, Node*> const& nodeMap = map().getNodeMap();
	for (unordered_map<string, Node*>::const_iterator node = nodeMap.begin(); node != nodeMap.end(); ++node) {
		addGameObject<NodeButton>(node->second, node->second->loadNode());
	}
}