#include "MapScene.h"
#include "../core/SDLApplication.h"
#include "../gameObjects/NodeButton.h"

MapScene::MapScene() : GameState(), nodeMap(Node::getNodeMap()) {
	for (vector<Node*>::const_iterator node = nodeMap.begin(); node != nodeMap.end(); ++node) {
		addGameObject<NodeButton>(node, (*node)->loadNode());
	}
}