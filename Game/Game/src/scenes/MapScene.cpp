#include "MapScene.h"
#include "../core/SDLApplication.h"
#include "../gameObjects/Node Objects/NodeButton.h"

MapScene::MapScene() {
	vector<vector<Node*>> const& nodeMap = map().getNodeMap();
	for (auto& height : nodeMap) {
		for (Node* node : height) {
			if (node != nullptr) addGameObject<NodeButton>(node, node->loadNode());
		}
	}
}